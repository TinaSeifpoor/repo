#include "features.h"
#include "listrandomsorter.h"
#include <QPair>
class FeaturesPrivate {
public:
    FeaturesPrivate(){}
    QList<Feature*> spannedFeatures;
    QList<Feature*> uniqueFeatures;

};

Features::Features(void):d(new FeaturesPrivate)
{
}

Features::Features(QList<Feature*> uniqueFeatureList):d(new FeaturesPrivate)
{
    int count = uniqueFeatureList.count();
    for (int i=0; i<count; ++i)
        (*this) << uniqueFeatureList.at(i);
}

void Features::operator <<(Feature *feature)
{
    unsigned int range = feature->parameterRange();
    for (int i=0;i<range;++i)
        d->spannedFeatures<<feature;
}

QList<Feature *> Features::getFullList() const
{
    return d->spannedFeatures;
}

QList<Feature *> Features::randomlySortedList(double ratio) const
{
    if (ratio==1) {
        return d->spannedFeatures;
    } else if(ratio < 1) {
        return randomlySortList(ratio,d->spannedFeatures);
    }
    else {
        return QList<Feature*>();
    }
}
