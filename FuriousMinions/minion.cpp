#include "minion.h"
#include "affiniteetemplate.h"
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
        notify();
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

    void notify() const
    {
        for (int i=0; i<objsToNotify.count(); ++i) {
            const char* member = membersToNotify.value(i);
            QObject* receiver = objsToNotify.value(i);
            if (member && receiver) {
                const char* bracketPosition = strchr(member, '(');
                if (!bracketPosition || !(member[0] >= '0' && member[0] <= '3')) {
                    qWarning("MinionData::notify: Invalid slot specification");
                    return;
                }
                QByteArray methodName(member+1, bracketPosition - 1 - member); // extract method name
                QMetaObject::invokeMethod(receiver, methodName.constData(), Qt::QueuedConnection);
            }
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
