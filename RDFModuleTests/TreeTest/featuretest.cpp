#include "featuretest.h"
#include <QFileInfo>
const int randomizer=50000;

Q_DECLARE_METATYPE(QFileInfo);
enum featureTestEnum {
    feature1 = 1,
    feature2 = 2,
    feature3 = 4
};
Q_DECLARE_FLAGS(featureTestFlags, featureTestEnum)
FeatureTest::FeatureTest(int index):
    index(index)
{
    if (index ==-1)
        range=3;
    else {
        range=1;
    }
}

unsigned int FeatureTest::parameterRange() const
{
    return this->range;
}

Feature *FeatureTest::getIndex(const unsigned int idx) const
{
    if (this->index==-1 && range>idx) {
        return new FeatureTest(idx);
    } else if (idx == 0){
        return new FeatureTest(index);
    }
    return 0;
}


bool FeatureTest::setSource(const Source *samples, const FeatureIdx idxFeature) const
{
    featureTestEnum feature;
    if (idxFeature==0) {
        feature = feature1;
    } else if (idxFeature==1) {
        feature = feature2;
    } else {
        feature = feature3;
    }
    for (uint idxSamples=0; idxSamples<samples->countSamples(); ++idxSamples) {
        Sample* sample = samples->at(idxSamples);
        int featureVal = sample->sampleClass&feature;
        sample->featureValues[idxFeature] = (getRand()-0.5)+featureVal;
    }
    return true;
}

double FeatureTest::getRand() const
{
    return (double)(qrand()%randomizer)/randomizer;
}
