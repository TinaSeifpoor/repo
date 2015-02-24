#include "minion.h"
#include "affiniteetemplate.h"
#include "miniondata.h"
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

Minion::Minion(MinionData* data) : __data(data)
{
}

Minion::~Minion()
{

}

QString Minion::getName() const
{
    return __data->minionName();
}

Rank Minion::getRank() const {
    return __data->getRank();
}

QString Minion::getMinionResourceIcon() const
{
    return __data->getMinionResourceIcon();

}

QList<AffinityTypes> Minion::getAffinities() const
{
    return __data->getAffinities();
}

Power Minion::getAffinityPower(AffinityTypes affinity) const
{
    return __data->getAffinityPower(affinity);
}

void Minion::setMinionTrigger(QObject *obj, const char *member)
{
    __data->addObj(obj, member);
}

void Minion::removeMinionTrigger(QObject *obj)
{
    __data->removeObj(obj);
}

void Minion::questComplete()
{
    __data->questCompleted();
}

QVariantHash Minion::toHash() const
{
    return __data->toHash();
}

Minion Minion::fromHash(QVariantHash hash)
{
    Minion mt(MinionData::fromHash(hash));
    return mt;
}
