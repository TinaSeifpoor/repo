#include "affiniteetemplate.h"

AffiniteeTemplate::AffiniteeTemplate()
{

}

AffiniteeTemplate::~AffiniteeTemplate()
{
}

void AffiniteeTemplate::set(AffinityTypes type, int seed)
{
    __seed = seed;
    setPowers(genAffinities(type));
}

int AffiniteeTemplate::get() const
{
    return __seed;
}

Power AffiniteeTemplate::getAffinityPower(AffinityTypes type) const
{
    return __affinityPowers.value(type,0);
}

QList<AffinityTypes> AffiniteeTemplate::getAffinities() const
{
    return __affinityPowers.keys();
}
