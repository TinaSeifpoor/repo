#ifndef QUESTPROGRESSHUB_H
#define QUESTPROGRESSHUB_H

#include <QWidget>
#include "minion.h"
class Quest;
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
    void questComplete(Minion returningMinion);
};

#endif // QUESTPROGRESSHUB_H
