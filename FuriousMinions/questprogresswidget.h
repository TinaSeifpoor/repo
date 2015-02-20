#ifndef QUESTPROGRESSWIDGET_H
#define QUESTPROGRESSWIDGET_H

#include "furiouspushbutton.h"
#include "minion.h"
class Quest;
class QuestProgressWidgetPrivate;
class QuestProgressWidget : public FuriousPushButton
{
    Q_OBJECT
    QuestProgressWidgetPrivate*d;
    friend class QuestProgressWidgetPrivate;
public:
    QuestProgressWidget(Minion minion, Quest quest, QWidget* parent=0);
    ~QuestProgressWidget();
public slots:
    void epoch();
private slots:
    void onClicked();
signals:
    void questReward(Minion reward);
};

#endif // QUESTPROGRESSWIDGET_H
