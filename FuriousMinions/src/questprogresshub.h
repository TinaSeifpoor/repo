#ifndef QUESTPROGRESSHUB_H
#define QUESTPROGRESSHUB_H

#include <QWidget>
#include "minion.h"
class Quest;
class QuestProgressHub : public QWidget
{
    Q_OBJECT
public:
    explicit QuestProgressHub(QWidget *parent = 0);
    ~QuestProgressHub();
    void startQuest(Minion minion, Quest quest);
signals:
    void questComplete(Minion returningMinion);
};

#endif // QUESTPROGRESSHUB_H
