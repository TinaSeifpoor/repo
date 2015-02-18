#ifndef QUESTHUB_H
#define QUESTHUB_H

#include <QWidget>
#include "quest.h"
class QuestSelectionWidget;
class QuestHub : public QWidget
{
    Q_OBJECT
public:
    explicit QuestHub(QWidget *parent = 0);
    ~QuestHub();
    void addQuest(Quest quest);
    void addQuestSelectionWidget(QuestSelectionWidget* qsw);
    QuestSelectionWidget* getQuestSelectionWidget();
};

#endif // QUESTHUB_H
