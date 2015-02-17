#include "minion.h"
#include "affiniteetemplate.h"
class MinionData : public AffiniteeTemplate
{
public:
    virtual void set(int seed);
    QString __minionName;
    // TODO: Experience / Talents etc.
};

void MinionData::set(int seed)
{
    AffiniteeTemplate::set(seed);
    __minionName = QString("Seed: %1 Affinities: (%2)").arg(get()).arg(affinityStringList(getAffinities()).join(", "));
}


Minion::Minion(const Minion &other):__data(other.__data)
{

}

Minion::Minion(int seed):__data(new MinionData())
{
    __data->set(seed);
}

Minion::Minion() : __data(new MinionData())
{
    __data->set(qrand());
}

Minion::~Minion()
{

}

QString Minion::getName() const
{
    return __data->__minionName;
}

Affinities Minion::getAffinities() const
{
    return __data->getAffinities();
}
