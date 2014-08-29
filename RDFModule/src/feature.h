#ifndef FEATURE_H
#define FEATURE_H
#include "source.h"
class Feature
{
public:
    virtual int parameterRange() const=0;
    virtual Feature* getIndex(const int idx) const=0;
    virtual bool setSource(const Source *samples, const FeatureIdx idxFeature) const=0;
    virtual int getIndex() const=0;
};

#endif // FEATURE_H
