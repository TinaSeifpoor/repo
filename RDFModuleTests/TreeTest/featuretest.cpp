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
        range=4;
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
    if (idxFeature==0) {
        feature = feature1;
    } else if (idxFeature==1) {
        feature = feature2;
    } else if (idxFeature==2) {
        feature = feature3;
    } else if (idxFeature==3) {
        feature = feature4;
    }
    for (int idxSamples=0; idxSamples<samples->countSamples(); ++idxSamples) {
        Sample* sample = samples->at(idxSamples);
        if (!sample->featureValues.contains(idxFeature)) {
            int featureVal = sample->sampleClass&feature;
            sample->featureValues[idxFeature] = (getRand()-0.5)*1.6+featureVal;
        }
    }
    return true;
}

double FeatureTest::getRand() const
{
    return (double)(qrand()%randomizer)/randomizer;
}
