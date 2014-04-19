#include "imageobject.h"
#include "common.h"
#include "instanceobject.h"

#include <QFileInfo>
#include <QVector>
#include <QStringList>
#include "common.h"
#include "opencv2/nonfree/features2d.hpp"

Q_DECLARE_METATYPE(cv::Mat)

class ImageObjectPrivate {
public:
    ImageObjectPrivate(){}

    QString imagePath;
    QString xmlPath;
    Image image;
    QHash<QString, InstanceObject*> data;
    void extract();
    QString name;
    bool isValid;
};

void ImageObjectPrivate::extract(){
    using namespace cv;
    QFileInfo fileInfo(imagePath);
    if (fileInfo.exists()) {
        this->name = fileInfo.completeBaseName();
        this->image = cv::imread(fileInfo.filePath().toStdString());
        if (!image.empty()) {
            KeyPoints keyPoints;
            uint nChannels = image.channels();
            Image imageGray;
            uint nCols = image.cols,
                    nRows = image.rows;
            Image imMask = Image(nRows, nCols, CV_8UC1, Scalar(255));

            if (nChannels == 3)
                cvtColor(image, imageGray, CV_BGR2GRAY);
            else
                image.copyTo(imageGray);

            //            SIFT fd(0, 5, 0.1, 10, 1.6);
            MSER fd;
            fd.detect(imageGray, keyPoints, imMask);

            for (unsigned int idx=0; idx<keyPoints.size(); ++idx) {
                this->data.insert(QString::number(idx),new InstanceObject(image, keyPoints.at(idx), idx));
            }
            isValid= true;
        }
        else {
            qWarning(QString("File can't be read: %1").arg(fileInfo.absoluteFilePath()).toLatin1().constData());
            isValid = false;
        }
    } else {
        qWarning(QString("File does not exist: %1").arg(fileInfo.absoluteFilePath()).toLatin1().constData());
        isValid = false;
    }
}

ImageObject::ImageObject(QString imagePath):d(new ImageObjectPrivate)
{
    d->imagePath = imagePath;
    d->extract();
}

ImageObject::ImageObject(QVariantHash data):d(new ImageObjectPrivate)
{
    QStringList dataKeys = data.keys();
    if (!data.contains("Name") ||
            !data.contains("Path")) {
        d->isValid = false;
        return;
    }

    d->name = data.value("Name").toString();
    d->imagePath = data.value("Path").toString();
    d->image = cv::imread(d->imagePath.toStdString());

    if (data.contains("InstanceList")) {
        QVariantHash instanceHash = data.value("InstanceList").toHash();

        QStringList keys = instanceHash.keys();

        foreach (QString key, keys) {
            InstanceObject* obj = new InstanceObject(d->image, instanceHash);
            d->data.insert(key, obj);
        }
    }
}

QString ImageObject::name() const
{
    return d->name;
}

InstanceObject *ImageObject::at(int idx)
{
    if (d->data.contains(QString::number(idx)))
        return d->data.value(QString::number(idx));
    else
        return 0
                ;
}

int ImageObject::count() const
{
    return d->data.count();
}

cv::Mat ImageObject::image() const
{
    return d->image;
}

bool ImageObject::isValid() const
{
    return d->isValid;
}

QString ImageObject::path() const
{
    return d->imagePath;
}

void ImageObject::addInstance(InstanceObject *obj)
{
    QString objName = obj->name();
    if (d->data.contains(objName)) {
        obj->setName(objName+"_");
        this->addInstance(obj);
        return;
    } else {
        d->data.insert(obj->name(), obj);
    }

}

void ImageObject::setName(QString name)
{
    d->name = name;
}

QVariantHash ImageObject::toHash() const
{
    QVariantHash output;
    QStringList keys = d->data.keys();
    QVariantHash imageHash;
    imageHash.insert("Path", d->imagePath);
    imageHash.insert("Name", d->name);
    QVariantHash instanceHash;

    foreach (QString key, keys) {
        instanceHash.unite(d->data.value(key)->toHash());
    }
    imageHash.insert("InstanceList", instanceHash);
    output.insertMulti(this->name(), imageHash);
    return output;
}


