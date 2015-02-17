#ifndef QUESTSELECTIONWIDGET_H
#define QUESTSELECTIONWIDGET_H

#include <QCheckBox>
#include "quest.h"
class QuestSelectionWidget : public QCheckBox
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
