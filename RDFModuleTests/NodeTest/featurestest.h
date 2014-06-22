#ifndef FEATURESTEST_H
#define FEATURESTEST_H
#include "../../RDFModule/src/features.h"
#include <QFileInfo>
class FeaturesTest : public Features
{
public:
    FeaturesTest();
    FeaturesTest(QList<Feature*> featureList);

    double getFeatureValue(int featureIdx) const;
    QPair<Feature *, int> at(int featureIdx) const;
};

#endif // FEATURESTEST_H
