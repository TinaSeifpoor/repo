#include "intermediateobject.h"
#include "opencvcommon.h"
#include "instanceobject.h"

#include <QFileInfo>
#include <QVector>
#include "opencv2/nonfree/features2d.hpp"
class IntermediateObjectPrivate {
public:
    QString path;
    Image image;
    QVector<InstanceObject*> data;
    QString name;
    bool valid;

    void extract();
};

void IntermediateObjectPrivate::extract(){
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
                this->data << new InstanceObject(image, keyPoints.at(idx), idx);
            }
            this->valid = true;
        }
        else {
            qWarning(QString("File can't be read: %1").arg(fileInfo.absoluteFilePath()).toLatin1().constData());
            this->valid = false;
        }
    } else {
        qWarning(QString("File does not exist: %1").arg(fileInfo.absoluteFilePath()).toLatin1().constData());
        this->valid = false;
    }
}

IntermediateObject::IntermediateObject(QString imagePath):d(new IntermediateObjectPrivate)
{
    d->path = imagePath;
    d->extract();
}

QString IntermediateObject::name() const
{
    return d->name;
}

RDFObject *IntermediateObject::at(int idx)
{
    if (idx<d->data.count() && idx > -1)
        return dynamic_cast<RDFObject*>(d->data.at(idx));
    else
        return 0;
}

int IntermediateObject::count() const
{
    return d->data.count();
}

bool IntermediateObject::isValid() const
{
    return d->valid;
}

cv::Mat IntermediateObject::image() const
{
    return d->image;
}


