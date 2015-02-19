#ifndef QUESTPROGRESSWIDGET_H
#define QUESTPROGRESSWIDGET_H

#include <QPushButton>
#include "reward.h"
class QuestProgressWidgetPrivate;
class QuestProgressWidget : public QPushButton
{
    Q_OBJECT
    QuestProgressWidgetPrivate*d;
    friend class QuestProgressWidgetPrivate;
public:
    QuestProgressWidget(Minion minion, Quest quest, QWidget* parent=0);
    ~QuestProgressWidget();
public slots:
    void epoch();

signals:
    void questReward(Reward reward);
};

#endif // QUESTPROGRESSWIDGET_H
