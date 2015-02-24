#ifndef QUESTPROGRESSHUB_H
#define QUESTPROGRESSHUB_H

#include <QWidget>
#include "minion.h"
#include "quest.h"
class QuestProgressWidget;
class QuestProgressHub : public QWidget
{
    Q_OBJECT
public:
    explicit QuestProgressHub(QWidget *parent = 0);
    ~QuestProgressHub();
    void startQuest(Minion minion, Quest quest);
    QVariantHash toHash() const;
    void fromHash(QVariantHash hash);
    void addQuestProgressWidget(QuestProgressWidget*qpw);
signals:
    void questReward(Minion returningMinion);
    void questComplete(Quest quest);
};

#endif // QUESTPROGRESSHUB_H
