#include "quest.h"
#include "affiniteetemplate.h"
#include "qmath.h"
class QuestData : public AffiniteeTemplate
{
    QList<QObject*> objsToNotify;
    QList<const char*> membersToNotify;
    int __questValue;
    int __questTime;
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

    double genValue(int seed) const
    {
        return seed%500000;
    }

    int genTime(int seed) const
    {
        int minTime = 60000;
        int maxTime = 300000;
        return minTime + seed%(maxTime-minTime);
    }
public:
    virtual void set(int seed)
    {
        AffiniteeTemplate::set(seed);
        __questValue = this->genValue(get());
        __questTime = this->genTime(get());
        notify();
    }
    int value() const {return __questValue;}
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

int Quest::getValue() const
{
    return __data->value();
}


Affinities Quest::getAffinities() const
{
    return __data->getAffinities();
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
