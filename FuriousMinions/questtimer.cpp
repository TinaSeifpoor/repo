#include "questtimer.h"
#include <QTimer>
#include "minion.h"
#include "quest.h"
class QuestData
{
public:
    QuestData(Minion minion, Quest quest) : minion(minion), quest(quest) {}
    Minion minion;
    Quest quest;
    QObject* questCompleteReceiver;
    const char* questCompleteMember;
    QTimer* questCompleteTimer;
    QObject* questUpdateReceiver;
    const char* questUpdateMember;
    QTimer* questUpdateTimer;
    int updateCount;
};

QuestTimer::QuestTimer(Minion minion, Quest quest) :
    QObject(),
    d(new QuestData(minion, quest))
{
    d->updateCount = 0;
}

void QuestTimer::questComplete()
{
    QObject* receiver = d->questCompleteReceiver;
    const char* member = d->questCompleteMember;
    if (member && receiver) {
        const char* bracketPosition = strchr(member, '(');
        if (!bracketPosition || !(member[0] >= '0' && member[0] <= '3')) {
            qWarning("QuestTimer::timeout: Invalid slot specification");
            return;
        }
        QByteArray methodName(member+1, bracketPosition - 1 - member); // extract method name
        QMetaObject::invokeMethod(receiver, methodName.constData(), Qt::QueuedConnection, Q_ARG(Minion, d->minion), Q_ARG(Quest, d->quest));
    }
    d->questUpdateTimer->deleteLater();
    d->questCompleteTimer->deleteLater();
    delete d;
    deleteLater();
}

void QuestTimer::questUpdate()
{
    ++d->updateCount;
    int remainingTime = d->quest.getTime()-d->updateCount*100;
    QObject* receiver = d->questUpdateReceiver;
    const char* member = d->questUpdateMember;
    if (member && receiver) {
        const char* bracketPosition = strchr(member, '(');
        if (!bracketPosition || !(member[0] >= '0' && member[0] <= '3')) {
            qWarning("QuestTimer::timeout: Invalid slot specification");
            return;
        }
        QByteArray methodName(member+1, bracketPosition - 1 - member); // extract method name
        QMetaObject::invokeMethod(receiver, methodName.constData(), Qt::QueuedConnection, Q_ARG(int, remainingTime));
    }
}

void QuestTimer::setQuestTimer(Minion minion, Quest quest, QObject *receiver, const char *member, QObject *questUpdateReceiver, const char *questUpdateMember)
{
    QuestTimer* qt= new QuestTimer(minion,quest);
    qt->d->questCompleteReceiver = receiver;
    qt->d->questCompleteMember = member;
    qt->d->questCompleteTimer = new QTimer(qt);
    qt->d->questCompleteTimer->setSingleShot(true);
    qt->connect(qt->d->questCompleteTimer, SIGNAL(timeout()), qt, SLOT(questComplete()));
    qt->d->questCompleteTimer->start(quest.getTime());


    qt->d->questUpdateReceiver = questUpdateReceiver;
    qt->d->questUpdateMember = questUpdateMember;
    qt->d->questUpdateTimer = new QTimer(qt);
    qt->d->questUpdateTimer->setSingleShot(false);
    qt->connect(qt->d->questUpdateTimer, SIGNAL(timeout()), qt, SLOT(questUpdate()));
    qt->d->questUpdateTimer->start(100);
}
