#ifndef FEATURES_H
#define FEATURES_H
#include <QList>
#include <QPair>
#include "feature.h"

class FeaturesPrivate;
class Features
{
public:
    explicit Features(void);
    Features(QList<Feature*> uniqueFeatureList);
    void operator << (Feature* feature);
    virtual QPair<Feature *, int> at(int featureIdx) const=0;
    double getFeatureValue(int featureIdx) const;
    QList<Feature*> getFullList() const;
    QList<Feature*> randomlySortedList(double ratio) const;

private:
    friend class FeaturesPrivate;
    FeaturesPrivate* d;

};
#endif // FEATURES_H
