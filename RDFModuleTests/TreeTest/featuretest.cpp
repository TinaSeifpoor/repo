#include "featuretest.h"
#include <QFileInfo>
const int randomizer=50000;

Q_DECLARE_METATYPE(QFileInfo);

FeatureTest::FeatureTest(int index):
    index(index)
{
    if (index ==-1)
        range=10;
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
    for (uint idxSamples=0; idxSamples<samples->countSamples(); ++idxSamples) {
        Sample* sample = samples->at(idxSamples);
        sample->featureValues[idxFeature] = getRand()/4+(double)((sample->sampleClass+idxFeature)%4);
    }
    return true;
}

double FeatureTest::getRand() const
{
    return (double)(qrand()%randomizer)/randomizer;
}
