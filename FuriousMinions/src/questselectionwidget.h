#ifndef QUESTSELECTIONWIDGET_H
#define QUESTSELECTIONWIDGET_H

#include "furiouspushbutton.h"
#include "quest.h"
class QuestSelectionWidget : public FuriousPushButton
{
    Q_OBJECT
    Quest __quest;
    void resetUI();
public:
    explicit QuestSelectionWidget(Quest quest, QWidget *parent = 0);
    ~QuestSelectionWidget();
    void reset();
    Quest getQuest() const;
    QVariantHash toHash() const;

signals:

public slots:
    void onResetTimerFinished();

};

#endif // QUESTSELECTIONWIDGET_H
