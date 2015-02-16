#ifndef AFFINITEETEMPLATE_H
#define AFFINITEETEMPLATE_H
#include "common.h"
class AffiniteeTemplate
{
    Affinities __affinities;
    int __seed;
protected:
    virtual void set(int seed);
    int get() const;
    Affinities getAffinities() const;
    AffiniteeTemplate();
    virtual ~AffiniteeTemplate();

};

#endif // AFFINITEETEMPLATE_H
