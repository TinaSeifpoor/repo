#ifndef IMAGECONTAINER_H
#define IMAGECONTAINER_H
#include "source.h"
#include <QDir>
#include <QHash>
#include <QVector>
#include "common.h"

class ImageContainer : public Source
{
public:
    ImageContainer();
    unsigned int countSamples();
    unsigned int countFeatures();

    Source* baggedSamples(double sampleRatio, double featureRatio);

    void setImageAndKeypoint(Image image, KeyPoints keyPoints);

private:
    QVector<Image> imageVector;
    QHash<int, KeyPoints> keypointVectorHash;

    int m_keypointCount;
};

#endif // IMAGECONTAINER_H
