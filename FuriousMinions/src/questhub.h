#ifndef QUESTHUB_H
#define QUESTHUB_H

#include <QWidget>
#include "minion.h"
class Quest;
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
    QVariantHash toHash() const;
    void fromHash(QVariantHash hash);
public slots:
};

#endif // QUESTHUB_H
