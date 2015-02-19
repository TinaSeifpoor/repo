#include "quest.h"
#include "affiniteetemplate.h"
#include "qmath.h"
#include <QTimer>
#include <QTime>
class QuestData : public AffiniteeTemplate
{
    QList<QObject*> objsToNotify;
    QList<const char*> membersToNotify;
    int __questTime;
    void notify() const
    {
        for (int i=0; i<objsToNotify.count(); ++i) {
            QTimer::singleShot(0,objsToNotify.value(i), membersToNotify.value(i));
        }
    }
    virtual QHash<AffinityTypes, Power> setPowers(QList<AffinityTypes> types) {
        QHash<AffinityTypes, Power> powers;
        foreach (AffinityTypes type, types) {
            powers.insert(type, qrand()%600 + 800);
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
public:
    virtual void set(int seed)
    {
        AffiniteeTemplate::set(seed);
        __questTime = this->genTime();
        notify();
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
private:
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

QString Quest::getText() const
{
    QStringList affinityTexts;
    foreach (AffinityTypes type, getAffinities()) {
        affinityTexts << QString("%1 (%2)").arg(affinityString(type)).arg(getAffinityPower(type));
    }
    QString affinityText = affinityTexts.join(", ");
    QTime time;
    return QString("Time: %1\n%2").arg(time.addMSecs(getTime()).toString()).arg(affinityText);
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
