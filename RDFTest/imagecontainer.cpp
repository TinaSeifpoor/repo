#include "imagecontainer.h"

using namespace cv;
ImageContainer::ImageContainer()
{
}

unsigned int ImageContainer::countSamples()
{
    return this->m_keypointCount;
}

unsigned int ImageContainer::countFeatures()
{
    return 3;
}

Source *ImageContainer::baggedSamples(double sampleRatio, double featureRatio)
{
    return static_cast<Source*>(new ImageContainer());
}

void ImageContainer::setImageAndKeypoint(Image image, KeyPoints keyPoints)
{
    this->imageVector << image;
    this->keypointVectorHash.insert(this->imageVector.count()-1, keyPoints);
    this->m_keypointCount+=(int)keyPoints.size();
    for (unsigned int i=0; i<keyPoints.size(); ++i) {
        qDebug(QString("Keypoint: angle (%1), octave (%2), size (%3), pt (%4,%5)").
               arg(QString::number(keyPoints[i].angle)).
               arg(QString::number(keyPoints[i].octave)).
               arg(QString::number(keyPoints[i].size)).
               arg(QString::number(keyPoints[i].pt.x)).
               arg(QString::number(keyPoints[i].pt.y)).toLatin1().constData());
    }
}
