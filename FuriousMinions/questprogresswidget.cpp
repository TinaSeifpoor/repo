#include "questprogresswidget.h"
#include <QPropertyAnimation>
#include "minion.h"
#include "quest.h"
#include <QDateTime>
#include "synchronizedtimer.h"
#include "reward.h"
class QuestProgressWidgetPrivate
{
public:
    QuestProgressWidgetPrivate(Quest quest, Minion minion, QuestProgressWidget* parent):p(parent),quest(quest),minion(minion){
        questEndTime = QDateTime::currentDateTime().addMSecs(quest.getTime()).toMSecsSinceEpoch();
        p->connect(SynchronizedTimer::getInstance(), SIGNAL(epoch()), p, SLOT(epoch()));
    }
    Quest quest;
    Minion minion;

    qint64 questEndTime;
    QuestProgressWidget* p;
};

QuestProgressWidget::QuestProgressWidget(Minion minion, Quest quest, QWidget *parent):
    QPushButton(parent),
    d(new QuestProgressWidgetPrivate(quest,minion,this))
{
    connect (this, SIGNAL(clicked()), SLOT(onClicked()));
    setEnabled(false);
}

QuestProgressWidget::~QuestProgressWidget()
{
    delete d;
}

void QuestProgressWidget::epoch()
{
    qint64 current = QDateTime::currentDateTime().toMSecsSinceEpoch();
    if (current > d->questEndTime) {
        setText(QString("Claim rewards!"));
        setEnabled(true);
    } else {
        QTime time;
        setText(QString("%1\n%2\nTime Left: %3").arg(d->minion.getName(),d->quest.getText(),
                                                     time.addMSecs(d->questEndTime-current).toString()));
    }
}

void QuestProgressWidget::onClicked()
{
    Reward::rewardGold(d->minion, d->quest);
    emit questReward(d->minion);
    deleteLater();
}
