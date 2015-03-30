#include "quest.h"
#include "affiniteetemplate.h"
#include "qmath.h"
#include <QTimer>
#include <QTime>
#include "globalvariables.h"
class QuestData : public AffiniteeTemplate
{
protected:
    QList<QObject*> objsToNotify;
    QList<const char*> membersToNotify;
    int __questTime;
    QString __textDescription;
    Rank __rank;
    QString __icon;
    void notify() const
    {
        for (int i=0; i<objsToNotify.count(); ++i) {
            QTimer::singleShot(0,objsToNotify.value(i), membersToNotify.value(i));
        }
    }
    virtual void setPowers(QList<AffinityTypes> types) {
        __affinityPowers.clear();
        foreach (AffinityTypes type, types) {
            Power affPower = qrand()%60 + 80;
            Power curPower = qPow(affPower,__rank);
            __affinityPowers.insert(type, curPower);
        }
    }

    int genTime() const
    {
        int nAffinities = getAffinities().count();
        int totalPower=0;
        foreach (AffinityTypes type, getAffinities())
            totalPower+=getAffinityPower(type);
        nAffinities*=2.5;
        int time = 1986*qLn(totalPower/nAffinities);
        return time;
    }

public:
    QVariantHash toHash() const {
        QVariantHash questHash;
        questHash.insert("Rank", __rank);
        questHash.insert("Seed", get());
        questHash.insert("Time", __questTime);
        questHash.insert("Icon", getQuestResourceIcon());
        questHash.insert("Name", getName());
        QVariantHash powersHash;
        foreach (AffinityTypes type, getAffinities()) {
            powersHash.insert(affinityString(type), getAffinityPower(type));
        }
        questHash.insert("Powers", powersHash);
        return questHash;
    }
    static QuestData* fromHash(QVariantHash hash) {
        QuestData* qd = new QuestData();
        qd->set(hash.value("Seed", qrand()).toInt());
        qd->__rank = hash.value("Rank",1).toInt();
        qd->__icon = hash.value("Icon",qd->__icon).toString();
        qd->__textDescription = hash.value("Name", qd->__textDescription).toString();
        qd->__questTime = hash.value("Time",qd->__questTime).toInt();
        qd->__affinityPowers.clear();
        QVariantHash powersHash = hash.value("Powers").toHash();
        foreach (QString affinityStr, powersHash.keys())
            qd->__affinityPowers.insert(affinityFromString(affinityStr),powersHash.value(affinityStr).toDouble());
        return qd;
    }

    QuestData() {}
    Rank getRank() const {return __rank;}
    virtual void set(AffinityTypes base, int seed, Rank rank=1)
    {
        __rank = rank;
        __textDescription = "Building";
        __icon = ":/icons/quests/35/quest1.gif";
        for (int i=0; i<__rank-1;++i)
            __textDescription.append('+');
        AffiniteeTemplate::set(base, seed);
        __questTime = this->genTime();
        notify();
//        GlobalVariables::addQuest(__rank);
    }

    QString getQuestResourceIcon() const
    {
        return __icon;
    }

    QString getName() const {
        return __textDescription;
    }
    ~QuestData() {
    }

    int time() const {return __questTime;}
    void setTime(int time) {
        __questTime = time;
        notify();
    }
    void addObj(QObject* obj, const char* member) {
        objsToNotify << obj;
        membersToNotify << member;
    }
};

Quest::Quest(const Quest &other) : __data(other.__data)
{

}

Quest::Quest(int seed, Rank rank) : __data(new QuestData())
{
    __data->set(seed,rank);
}

Quest::~Quest()
{

}

Quest::Quest(Rank rank):__data(new QuestData()){
    __data->set(qrand(),rank);
}

Quest::Quest(QuestData *data): __data(data)
{
}

int Quest::getTime() const
{
    return __data->time();
}

Power Quest::getAffinityPower(AffinityTypes type) const
{
    return __data->getAffinityPower(type);
}

QList<AffinityTypes> Quest::getAffinities() const
{
    return __data->getAffinities();
}

QVariantHash Quest::toHash() const
{
    return __data->toHash();
}

Quest Quest::fromHash(QVariantHash hash)
{
    return Quest(QuestData::fromHash(hash));
}

QString Quest::getName() const
{
    return __data->getName();
}

QString Quest::getTimeText() const
{
    return QTime::fromString("00:00:00:000", "hh:mm:ss:zzz").addMSecs(getTime()).toString();
}

QString Quest::getQuestResourceIcon() const
{
    return __data->getQuestResourceIcon();

}

Rank Quest::getRank() const
{
    return __data->getRank();
}

void Quest::reset()
{
    __data.detach();
    __data->set(qrand());
}

void Quest::setQuestTrigger(QObject *obj, const char *member)
{
    __data->addObj(obj, member);
}
