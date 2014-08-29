#ifndef FEATURETEST_H
#define FEATURETEST_H
#include "feature.h"
#include "common.h"
class FeatureTest : public Feature
{
public:
    explicit FeatureTest(int index=-1);
    int parameterRange() const;
    Feature* getIndex(const int idx) const;
    bool setSource(const Source *samples, const FeatureIdx idxFeature) const;
    int getIndex() const;

private:
    int index;
    int range;
    int sample;
    double getRand() const;

};

#endif // FEATURETEST_H
