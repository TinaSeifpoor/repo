#ifndef QUESTSELECTIONWIDGET_H
#define QUESTSELECTIONWIDGET_H

#include <QPushButton>
#include "quest.h"
class QuestSelectionWidget : public QPushButton
{
    Q_OBJECT
    Quest __quest;
    void resetUI();
public:
    explicit QuestSelectionWidget(Quest quest, QWidget *parent = 0);
    ~QuestSelectionWidget();
    void reset();

    Quest getQuest() const;

signals:

public slots:
    void onResetTimerFinished();

};

#endif // QUESTSELECTIONWIDGET_H
