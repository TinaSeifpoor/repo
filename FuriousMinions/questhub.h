#ifndef QUESTHUB_H
#define QUESTHUB_H

#include <QWidget>
#include "quest.h"
class QuestHub : public QWidget
{
    Q_OBJECT
public:
    explicit QuestHub(QWidget *parent = 0);
    ~QuestHub();
    void addQuest(Quest quest);
    Quest getQuest();
};

#endif // QUESTHUB_H
