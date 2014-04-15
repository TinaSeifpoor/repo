#include "imageobject.h"
#include "common.h"
#include "instanceobject.h"
#include "featureextractor.h"

#include <QFileInfo>
#include <QVector>
#include "common.h"
#include "opencv2/nonfree/features2d.hpp"
class ImageObjectPrivate {
public:
    QString path;
    Image image;
    QVector<InstanceObject*> data;
    void extract();
    QString name;
};

void ImageObjectPrivate::extract(){
    using namespace cv;
    QFileInfo fileInfo(path);
    if (fileInfo.exists()) {
        this->name = fileInfo.fileName();
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

            SIFT fd(0, 5, 0.1, 10, 1.6);
            fd.detect(imageGray, keyPoints, imMask);

            for (unsigned int idx=0; idx<keyPoints.size(); ++idx) {
//                InstanceObject o(keyPoint);
                this->data << new InstanceObject(image, keyPoints.at(idx), idx);
//                this->data << o;
            }
        }
        else {
            qWarning(QString("File can't be read: %1").arg(fileInfo.absoluteFilePath()).toLatin1().constData());
        }
    } else {
        qWarning(QString("File does not exist: %1").arg(fileInfo.absoluteFilePath()).toLatin1().constData());
    }
}

ImageObject::ImageObject(QString imagePath):d(new ImageObjectPrivate)
{
    d->path = imagePath;
    d->extract();
}

QString ImageObject::name() const
{
    return d->name;
}

InstanceObject *ImageObject::at(int idx)
{
    if (idx<d->data.count() && idx > -1)
        return d->data.at(idx);
    else
        return 0;
}

int ImageObject::count() const
{
    return d->data.count();
}

cv::Mat ImageObject::image() const
{
    return d->image;
}


