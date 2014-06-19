#include "features.h"
#include "listrandomsorter.h"
#include "sample.h"
class FeaturesPrivate {
public:
    FeaturesPrivate(){}
    QList<Feature*> features;

};

Features::Features():d(new FeaturesPrivate)
{
}

Features::Features(QList<Feature *> features)
{
    d->features = features;
}

void Features::operator <<(Feature *feature)
{
    unsigned int range = feature->parameterRange();
    QList<Feature*>::Iterator begin = d->features.end();
    d->features.reserve(d->features.count()+range);
    QList<Feature*>::Iterator end = d->features.end();
    qFill(begin,end,feature);
}

Features *Features::randomlySort(double ratio) const
{
    return new Features(randomlySortList(ratio,d->features));
}

double Features::getFeatureValue(int i, Sample sample)
{
    d->features.at(i)->parameterValue(i, sample);
    return 5;
}
