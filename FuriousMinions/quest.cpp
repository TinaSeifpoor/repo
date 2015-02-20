#include "quest.h"
#include "affiniteetemplate.h"
#include "qmath.h"
#include <QTimer>
#include <QTime>
#include <QPixmap>
#include <QTextDocument>
#include <QPainter>
QHash<Rank, int> questCounterHash;
int questCounter=0;
class QuestData : public AffiniteeTemplate
{
protected:
    QList<QObject*> objsToNotify;
    QList<const char*> membersToNotify;
    int __questTime;
    QString __textDescription;
    Rank __rank;
    void notify() const
    {
        for (int i=0; i<objsToNotify.count(); ++i) {
            QTimer::singleShot(0,objsToNotify.value(i), membersToNotify.value(i));
        }
    }
    virtual QHash<AffinityTypes, Power> setPowers(QList<AffinityTypes> types) {
        QHash<AffinityTypes, Power> powers;
        foreach (AffinityTypes type, types) {
            Power affPower = qrand()%60 + 80;
            Power curPower = qPow(affPower,__rank);
            if (curPower<0) {
                qDebug(QString("Negative value from: %1, %2, %3").arg(affPower).arg(__rank).arg(curPower).toLatin1());
            }
            powers.insert(type, curPower);
        }
        return powers;
    }

    int genTime() const
    {
        int nAffinities = getAffinities().count();
        int totalPower=0;
        foreach (AffinityTypes type, getAffinities())
            totalPower+=getAffinityPower(type);
        nAffinities*=2.5;
        int time = 86*totalPower/nAffinities;
        return time;
    }

    Rank nextRank()
    {
        return calculateNextRank(questCounterHash);
    }

public:
    QuestData() {}
    Rank getRank() const {return __rank;}
    virtual void set(int seed)
    {
        __rank = nextRank();
        __textDescription = "Building";
        for (int i=0; i<__rank-1;++i)
            __textDescription.append('+');
        AffiniteeTemplate::set(seed);
        __questTime = this->genTime();
        notify();
    }
    void markComplete() {
        questCounterHash[__rank]++;
    }

    QString getQuestResourceIcon() const
    {
        return ":/icons/quests/35/quest1.gif";
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

Quest::Quest(int seed) : __data(new QuestData())
{
    __data->set(seed);
}

Quest::~Quest()
{

}

Quest::Quest():__data(new QuestData()){
    __data->set(qrand());
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

QString Quest::getName() const
{
    return __data->getName();
}

QString Quest::getTimeText() const
{
    return QTime().addMSecs(getTime()).toString();
}

QString Quest::getQuestResourceIcon() const
{
    return __data->getQuestResourceIcon();

}

Rank Quest::getRank() const
{
    return __data->getRank();
}

void Quest::markComplete()
{
    __data->markComplete();
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
