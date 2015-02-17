#ifndef AFFINITEETEMPLATE_H
#define AFFINITEETEMPLATE_H
#include "common.h"
#include <QSharedData>
class AffiniteeTemplate : public QSharedData
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
