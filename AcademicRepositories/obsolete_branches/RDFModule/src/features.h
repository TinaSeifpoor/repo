#ifndef FEATURES_H
#define FEATURES_H
#include <QList>
#include <vector>
#include "feature.h"
#include "common.h"
class Source;
class FeaturesPrivate;
class RDFMODULESHARED_EXPORT Features
{
public:
    void init();
    void operator << (Feature *feature);
    std::vector<double> getFeatureValues(const int featureIdx, bool *res=0) const;
    void setSource(const Source *samples);
    Features *baggedFeatures(double ratio) const;
    virtual Features* copy(QHash<int, Feature*> featureList) const=0;
    const int range() const;
    QList<int> featureIdxList() const;

protected:
    Feature * at(const int featureIdx) const;
    virtual void calculateFeatureValues(FeatureIdx featureIdx)=0;
    const Source *getSamples();

private:
    friend class FeaturesPrivate;
    FeaturesPrivate* d;

};
#endif // FEATURES_H
