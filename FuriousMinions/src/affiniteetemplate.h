#ifndef AFFINITEETEMPLATE_H
#define AFFINITEETEMPLATE_H
#include "common.h"
#include <QSharedData>
#include <QHash>
class AffiniteeTemplate : public QSharedData
{
    int __seed;
protected:
    QHash<AffinityTypes, Power> __affinityPowers;
    virtual void set(int seed);
    virtual void setPowers(QList<AffinityTypes>)=0;
    int get() const;
    AffiniteeTemplate();
    virtual ~AffiniteeTemplate();
public:
    Power getAffinityPower(AffinityTypes type) const;
    QList<AffinityTypes> getAffinities() const;
};

#endif // AFFINITEETEMPLATE_H
