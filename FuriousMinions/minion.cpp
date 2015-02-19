#include "minion.h"
#include "affiniteetemplate.h"
#include <QTimer>
int minionCounter=0;
class MinionData : public AffiniteeTemplate
{
    QString __minionName;
    double __experience;
    QList<QObject*> objsToNotify;
    QList<const char*> membersToNotify;
    void setName() {
        __minionName = QString("Experience: %1 Affinities: (%2)").arg(__experience).arg(affinityStringList(getAffinities()).join(", "));
    }
public:
    virtual void set(int seed)
    {
        AffiniteeTemplate::set(seed);
        __experience = 0;
        setName();
        minionCounter++;
        notify();
    }

    ~MinionData() {
        minionCounter--;
    }

    virtual bool addExperience(double experience) {
        bool isLevelUp=false;
        if (numDigits(__experience)<numDigits(__experience+experience))
            isLevelUp=true;
        __experience+=experience;
        setName();
        notify();
        // check if lvl up
        return isLevelUp;
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

    // TODO: Experience / Talents etc.
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

Affinities Minion::getAffinities() const
{
    return __data->getAffinities();
}

double Minion::getBasePower() const
{
    return 20;
}

double Minion::getAffinityPower(AffinityTypes affinity) const
{
    return 50;
}

bool Minion::rewardExperience(double experience)
{
    return __data->addExperience(experience);
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
