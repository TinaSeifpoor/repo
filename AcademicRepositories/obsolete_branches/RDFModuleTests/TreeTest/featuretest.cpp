#include "featuretest.h"
#include <QFileInfo>
const int randomizer=50000;

Q_DECLARE_METATYPE(QFileInfo);
enum featureTestEnum {
    feature1 = 1,
    feature2 = 2,
    feature3 = 4,
    feature4 = 8
};
Q_DECLARE_FLAGS(featureTestFlags, featureTestEnum)
FeatureTest::FeatureTest(int index):
    index(index)
{
    if (index ==-1)
        range=1500;
    else {
        range=1;
    }
}

int FeatureTest::parameterRange() const
{
    return this->range;
}

Feature *FeatureTest::getIndex(const int idx) const
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
    if (idxFeature%feature4==0) {
        feature = feature4;
    } else if (idxFeature%feature4==1) {
        feature = feature1;
    } else if (idxFeature%feature4==2) {
        feature = feature2;
    } else {
        feature = feature3;
    }
    for (int idxSamples=0; idxSamples<samples->countSamples(); ++idxSamples) {
        Sample* sample = samples->at(idxSamples);
        if (!sample->featureValues.contains(idxFeature)) {
            int featureVal = sample->sampleClass&feature;
            sample->featureValues[idxFeature] = (getRand()-0.5)+featureVal;
        }
    }
    return true;
}

int FeatureTest::getIndex() const
{
    if (range == 1) {
        return this->index;
    } else {
        return -1;
    }
}

double FeatureTest::getRand() const
{
    return (double)(qrand()%randomizer)/randomizer;
}
