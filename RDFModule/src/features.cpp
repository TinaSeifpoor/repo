#include "features.h"
#include "listrandomsorter.h"
#include "source.h"
#include <QVector>
#include <QPair>
struct Sample;
class FeaturesPrivate {
public:
    FeaturesPrivate(){}
    QList<Feature*> features;
    const Source *samples;
    QList<bool> featureCalculated;
};

void Features::init()
{
    d = new FeaturesPrivate;
}

void Features::operator <<(const Feature *feature)
{
    int nFeature = feature->parameterRange();
    for (int i=0; i<(int)nFeature;++i) {
        d->features.append(feature->getIndex(i));
    }
}

//double Features::getFeatureValue(const int linearIdx, bool *res) const
//{
//    if (d->features.size()>linearIdx) {
//        return d->features.at(linearIdx)->getParameterValue(res);
//    } else {
//        *res = false;
//        return INT_MIN;
//    }
//}

std::vector<double> Features::getFeatureValues(const int featureIdx, bool *res) const
{
    if (d->features.size()>featureIdx) {
        std::vector<double> featureValues;
        for (int idxSample=0; idxSample<(int)d->samples->countSamples(); ++idxSample) {
            featureValues.push_back(d->samples->at(idxSample)->featureValues[featureIdx]);
        }
        if (res!=0)
            *res = true;
        return featureValues;
    } else {
        if (res!=0)
            *res = false;
        return std::vector<double>();
    }
}

void Features::setSource(const Source *samples)
{
    d->samples = samples;
    for (int idxFeature=0; idxFeature<d->features.count(); ++idxFeature)
        this->calculateFeatureValues(idxFeature);
}

const int Features::range() const
{
    return d->features.count();
}

Features* Features::baggedFeatures(double ratio) const
{
    if (ratio==1) {
        return this->copy(d->features);
    } else if(ratio < 1) {
        return this->copy(randomlySortList(ratio,d->features));
    }
    else {
        return 0;
    }
}

Feature *Features::at(const int linearIdx) const
{
    if (linearIdx<d->features.count() && linearIdx>-1)
        return d->features.at(linearIdx);
    else
        return 0;
}

const Source *Features::getSamples()
{
    return d->samples;
}
