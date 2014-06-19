#include "sourcetest.h"
#include "features.h"
#include "listrandomsorter.h"
#include "sample.h"
class SourceTestPrivate {
public:
    SourceTestPrivate() {}
    unsigned int nSamples;
    unsigned int nFeatures;
    unsigned int nClasses;
    QFileInfoList fileInfoList;
    Features* features;
    QList<Sample> sampleList;
};

SourceTest::SourceTest(QFileInfoList fileInfoList, Features* features):
    d(new SourceTestPrivate)
{
    d->fileInfoList = fileInfoList;
    d->features = features;
}

unsigned int SourceTest::countSamples() const
{
    return d->nSamples;
}

unsigned int SourceTest::countFeatures() const
{
    return d->nFeatures;
}

unsigned int SourceTest::countClasses() const
{
    return d->nClasses;
}

Source *SourceTest::baggedSamples(double sampleRatio, double featureRatio) const
{
    return new SourceTest(randomlySortList(sampleRatio,d->fileInfoList),d->features->randomlySort(featureRatio));
}

Features *SourceTest::getFeatures() const
{
    return d->features;
}

std::vector<double> SourceTest::getFeatureValues(unsigned int idxFeature) const
{
    std::vector<double> featureValues;
    featureValues.resize(d->nSamples);
    std::vector<double>::iterator featureValuesIt = featureValues.begin();
    std::vector<double>::iterator featureValuesEnd = featureValues.end();

    for (int i=0;featureValuesIt!=featureValuesEnd;++featureValuesIt, ++i) {
        *(featureValuesIt) = d->features->getFeatureValue(idxFeature, d->sampleList.at(i));
    }
    return std::vector<double>();
}

QList<ClassID> SourceTest::getSampleClasses() const
{
    return QList<ClassID>();
}
