#ifndef FEATURETEST_H
#define FEATURETEST_H
#include "feature.h"
#include "common.h"
class FeatureTest : public Feature
{
public:
    explicit FeatureTest(int index=-1);
    unsigned int parameterRange() const;
    Feature* getIndex(const unsigned int idx) const;
    bool setSource(const Source *samples, const FeatureIdx idxFeature) const;

private:
    unsigned int index;
    unsigned int range;
    int sample;
    double getRand() const;

};

#endif // FEATURETEST_H
