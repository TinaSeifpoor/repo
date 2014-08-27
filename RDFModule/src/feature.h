#ifndef FEATURE_H
#define FEATURE_H
#include "source.h"
class Feature
{
public:
    virtual unsigned int parameterRange() const=0;
    virtual Feature* getIndex(const unsigned int idx) const=0;
    virtual bool setSource(const Source *samples, const FeatureIdx idxFeature) const=0;
};

#endif // FEATURE_H