#include "minion.h"
#include "affiniteetemplate.h"
#include <QTimer>
#include <QHash>
int minionCounter=0;
QHash<MinionRank, Minion> allMinions;
class MinionData : public AffiniteeTemplate
{
    QString __minionName;
    QList<QObject*> objsToNotify;
    QList<const char*> membersToNotify;
    void setName() {
        __minionName.clear();
        QStringList affinityTexts;
        foreach (AffinityTypes type, getAffinities()) {
            affinityTexts << QString("%1 (%2)").arg(affinityString(type)).arg(getAffinityPower(type));
        }
        __minionName = affinityTexts.join(", ");
    }
    virtual QHash<AffinityTypes, Power> setPowers(QList<AffinityTypes> types) {
        QHash<AffinityTypes, Power> powers;
        foreach (AffinityTypes type, types) {
            powers.insert(type, qrand()%80 + 30);
        }
        return powers;
    }

public:
    virtual void set(int seed)
    {
        AffiniteeTemplate::set(seed);
        setName();
        minionCounter++;
        notify();
    }

    ~MinionData() {
        minionCounter--;
    }



    QString minionName() const {return __minionName;}

    void addObj(QObject* obj, const char* member) {
        objsToNotify << obj;
        membersToNotify << member;
    }

    void removeObj(QObject* obj) {
        int i = objsToNotify.indexOf(obj);
        if (i!=-1) {
            objsToNotify.removeAt(i);
            membersToNotify.removeAt(i);
        }
    }

    void notify() const
    {
        for (int i=0; i<objsToNotify.count(); ++i) {
            QTimer::singleShot(0,objsToNotify.value(i), membersToNotify.value(i));
        }
    }
};




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
    return __data->minionName();
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

int Minion::totalNumberOfMinions()
{
    return minionCounter;
}
#include "qmath.h"
GoldCurrency Minion::nextMinionGold()
{
    if (totalNumberOfMinions()==0)
        return 50;
    return qPow(50,totalNumberOfMinions())+50;
}
