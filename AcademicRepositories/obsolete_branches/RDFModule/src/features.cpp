#include "features.h"
#include "listrandomsorter.h"
#include "source.h"
#include <QVector>
#include <QPair>
struct Sample;
class FeaturesPrivate {
public:
    FeaturesPrivate(){samples=0;}
    QHash<int,Feature*> features;
    const Source *samples;
    QList<bool> featureCalculated;
};

void Features::init()
{
    d = new FeaturesPrivate;
}

void Features::operator <<(Feature *feature)
{
    int nFeature = feature->parameterRange();
    if (nFeature==1) {
        d->features.insert(feature->getIndex(), feature);
    } else {
        for (int i=0; i<(int)nFeature;++i) {
            d->features.insert(i,feature->getIndex(i));
        }
    }
}

std::vector<double> Features::getFeatureValues(const int featureIdx, bool *res) const
{
    if (d->features.contains(featureIdx)) {
        std::vector<double> featureValues;
        for (int idxSample=0; idxSample<(int)d->samples->countSamples(); ++idxSample) {
            featureValues.push_back(d->samples->at(idxSample)->featureValues[featureIdx]);
        }
        if (res!=0)
            *res = true;
        return featureValues;
    }
    if (res!=0)
        *res = false;
    return std::vector<double>();
}

void Features::setSource(const Source *samples)
{
    if (d->samples)
        delete d->samples;
    d->samples = samples;
    foreach (int featureIdx, d->features.keys())
        this->calculateFeatureValues(featureIdx);
}

const int Features::range() const
{
    return d->features.count();
}

QList<int> Features::featureIdxList() const
{
    return d->features.keys();
}

Features* Features::baggedFeatures(double ratio) const
{
    if (ratio==1) {
        return this->copy(d->features);
    } else if(ratio < 1) {
        QList<int> selectedIdx = randomlySortList(ratio,d->features.keys());
        QHash<int, Feature*> hash;
        for ( int i=0; i<selectedIdx.count(); ++i) {
            hash.insert(selectedIdx.at(i), d->features.value(selectedIdx.at(i)));
        }
        return this->copy(hash);
    }
    else {
        return 0;
    }
}

Feature *Features::at(const int featureIdx) const
{
    if (d->features.contains(featureIdx))
        return d->features.value(featureIdx);
    else
        return 0;
}

const Source *Features::getSamples()
{
    return d->samples;
}
