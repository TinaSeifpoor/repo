#ifndef FEATURES_H
#define FEATURES_H
#include <QList>
#include <vector>
#include "feature.h"
#include "common.h"
class Source;
class FeaturesPrivate;
class Features
{
public:
    void init();
//    Features(QList<Feature*> featureList);
    void operator << (const Feature* feature);
    double getFeatureValue(const int linearIdx, bool *res=0) const;
    std::vector<double> getFeatureValues(const int featureIdx, bool *res=0) const;
    void setSource(const Source *samples);
    Features *randomlySortedList(double ratio) const;
    virtual Features* copy(QList<Feature*> featureList) const=0;
    const int range() const;
protected:
    Feature * at(const int linearIdx) const;
    virtual void calculateFeatureValues(FeatureIdx featureIdx)=0;
    const Source *getSamples();

private:
    friend class FeaturesPrivate;
    FeaturesPrivate* d;

};
#endif // FEATURES_H
