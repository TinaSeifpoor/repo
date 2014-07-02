#ifndef FEATURETEST_H
#define FEATURETEST_H
#include "../../RDFModule/src/feature.h"
#include "../../RDFModule/src/source.h"
#include "../../RDFModule/src/common.h"
class FeatureTest : public Feature
{
public:
    explicit FeatureTest(int index=-1);
//    explicit FeatureTest(const FeatureTest &other);
    double parameterValue(int featureIdx=-1, bool *res=0) const;
    unsigned int parameterRange() const;
    Feature* getIndex(const unsigned int idx) const;
    double getParameterValue(bool *res=0) const;
    bool setSource(const Source *samples, const FeatureIdx idxFeature);
//    QFileInfo getSource() const;

private:
    unsigned int index;
    unsigned int range;
    int sample;
};

#endif // FEATURETEST_H
