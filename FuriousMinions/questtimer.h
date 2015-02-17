#ifndef QUESTTIMER_H
#define QUESTTIMER_H

#include <QObject>
#include "minion.h"
#include "quest.h"
class QuestData;
class QuestTimer : private QObject
{
    Q_OBJECT
    QuestData *d;
    explicit QuestTimer(Minion minion, Quest quest);
private slots:
    void questComplete();
    void questUpdate();
public:
    static void setQuestTimer(Minion minion, Quest quest, QObject* questCompleteReceiver,
                              const char* questCompleteMember, QObject* questUpdateReceiver=0,
                              const char* questUpdateMember=0);
};

#endif // QUESTTIMER_H
