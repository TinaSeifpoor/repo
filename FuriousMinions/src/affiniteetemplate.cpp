#include "affiniteetemplate.h"

AffiniteeTemplate::AffiniteeTemplate()
{
}

AffiniteeTemplate::~AffiniteeTemplate()
{
}

void AffiniteeTemplate::set(int seed)
{
    __seed = seed;
    __affinityPowers = setPowers(genAffinities(seed));
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
