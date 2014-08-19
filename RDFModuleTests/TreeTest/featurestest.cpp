#include "featurestest.h"
#include "featuretest.h"
FeaturesTest::FeaturesTest()
{
    this->init();
    (*this) << new FeatureTest;
}

Features *FeaturesTest::copy(QList<Feature *> featureList) const
{
    return new FeaturesTest(featureList);
}


FeaturesTest::FeaturesTest(Feature *feature)
{
    this->init();
    (*this) << feature;
}
FeaturesTest::FeaturesTest(QList<Feature* > features)
{
    this->init();
    for (int i=0; i<features.count(); ++i)
        (*this) << features.at(i);
}

void FeaturesTest::calculateFeatureValues(FeatureIdx featureIdx)
{
    dynamic_cast<FeatureTest*>(Features::at(featureIdx))->setSource(getSamples(),featureIdx);
}
