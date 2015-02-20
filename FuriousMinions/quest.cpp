#include "quest.h"
#include "affiniteetemplate.h"
#include "qmath.h"
#include <QTimer>
#include <QTime>
#include <QPixmap>
#include <QTextDocument>
#include <QPainter>
class QuestData : public AffiniteeTemplate
{
protected:
    QList<QObject*> objsToNotify;
    QList<const char*> membersToNotify;
    int __questTime;
    QString __textDescription;
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
    QuestData() {}
    virtual void set(int seed)
    {
        __textDescription = "Building";
        AffiniteeTemplate::set(seed);
        __questTime = this->genTime();
        notify();
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

void Quest::reset()
{
    __data.detach();
    __data->set(qrand());
}

void Quest::setQuestTrigger(QObject *obj, const char *member)
{
    __data->addObj(obj, member);
}
