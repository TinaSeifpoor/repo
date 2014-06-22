#include "sourcetest.h"
#include "../../RDFModule/src/listrandomsorter.h"
class SourceTestPrivate {
public:
    SourceTestPrivate() {}
    unsigned int nSamples;
    unsigned int nFeatures;
    unsigned int nClasses;
    QFileInfoList fileInfoList;
    const FeaturesTest* features;
};

SourceTest::SourceTest(QFileInfoList fileInfoList, const FeaturesTest* features):
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
    QFileInfoList baggedSampleList = randomlySortList(sampleRatio,d->fileInfoList);
    FeaturesTest* ft = new FeaturesTest(d->features->randomlySortedList(featureRatio));
    return new SourceTest(baggedSampleList,ft);
}

const Features *SourceTest::getFeatures() const
{
    return dynamic_cast<const Features*>(d->features);
}

std::vector<double> SourceTest::getFeatureValues(unsigned int idxFeature) const
{
    std::vector<double> featureValues;
    featureValues.resize(d->nSamples);
    std::vector<double>::iterator featureValuesIt = featureValues.begin();
    std::vector<double>::iterator featureValuesEnd = featureValues.end();

    for (int i=0;featureValuesIt!=featureValuesEnd;++featureValuesIt, ++i) {
        // set source
        *(featureValuesIt) = d->features->getFeatureValue(idxFeature);
    }
    return std::vector<double>();
}

QList<ClassID> SourceTest::getSampleClasses() const
{
    return QList<ClassID>();
}
