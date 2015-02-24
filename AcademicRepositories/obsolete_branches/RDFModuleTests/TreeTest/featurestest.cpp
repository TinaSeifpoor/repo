#include "featurestest.h"
#include "featuretest.h"
FeaturesTest::FeaturesTest()
{
    this->init();
    (*this) << new FeatureTest;
}

Features *FeaturesTest::copy(QHash<int,Feature *> featureList) const
{
    return new FeaturesTest(featureList);
}


FeaturesTest::FeaturesTest(Feature *feature)
{
    this->init();
    (*this) << feature;
}
FeaturesTest::FeaturesTest(QHash<int, Feature *> features)
{
    this->init();
    foreach (int i, features.keys())
        (*this) << features.value(i);
}

void FeaturesTest::calculateFeatureValues(FeatureIdx featureIdx)
{
    FeatureTest* ft = dynamic_cast<FeatureTest*>(Features::at(featureIdx));
    if (ft)
        ft->setSource(getSamples(),featureIdx);
}
