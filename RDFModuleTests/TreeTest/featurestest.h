#ifndef FEATURESTEST_H
#define FEATURESTEST_H
#include "features.h"
#include <QFileInfo>
class FeaturesTest : public Features
{
public:
    FeaturesTest();

    Features* copy(QList<Feature *> featureList) const;
    FeaturesTest(Feature *feature);
    FeaturesTest(QList<Feature *> features);
    void calculateFeatureValues(FeatureIdx featureIdx);
};

#endif // FEATURESTEST_H
