#ifndef FEATURETEST_H
#define FEATURETEST_H
#include "../../RDFModule/src/feature.h"
class QFileInfo;
class FeatureTest : public Feature
{
public:
    FeatureTest();
    double parameterValue(int featureIdx, QFileInfo sample);
    unsigned int parameterRange() const;
};

#endif // FEATURETEST_H
