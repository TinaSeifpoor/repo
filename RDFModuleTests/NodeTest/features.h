#ifndef FEATURETEST_H
#define FEATURETEST_H
#include <QList>
#include "feature.h"
class Sample;
class Source;
class FeaturesPrivate;
class Features
{
public:
    Features();
    void operator << (Feature* feature);
    Features* randomlySort(double ratio) const;
    double getFeatureValue(int i, Sample sample);
private:
    Features(QList<Feature*> features);
    friend class FeaturesPrivate;
    FeaturesPrivate* d;

};
#endif // FEATURETEST_H
