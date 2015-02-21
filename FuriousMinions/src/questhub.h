#ifndef QUESTHUB_H
#define QUESTHUB_H

#include <QWidget>
#include "minion.h"
#include "quest.h"
class QuestSelectionWidget;
class FuriousPushButton;
class QuestHub : public QWidget
{
    Q_OBJECT
    FuriousPushButton* nextButton;
    FuriousPushButton* previousButton;
    Rank hubRank;
public:
    explicit QuestHub(QWidget *parent = 0);
    ~QuestHub();
    void addQuest(Quest quest);
    void addQuest();
    void addQuestSelectionWidget(QuestSelectionWidget* qsw);
    QuestSelectionWidget* getQuestSelectionWidget();
    QVariantHash toHash() const;
    void fromHash(QVariantHash hash);
    void setRank(Rank rank);
    void clear();
    void fillQuests();
signals:
    void rankChanged();
public slots:
    void nextRank();
    void prevRank();
    void questComplete(Quest quest);
};

#endif // QUESTHUB_H
