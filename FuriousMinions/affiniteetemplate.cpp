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
    __affinities = genAffinities(seed);
}

int AffiniteeTemplate::get() const
{
    return __seed;
}

Affinities AffiniteeTemplate::getAffinities() const
{
    return __affinities;
}
