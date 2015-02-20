#include "questprogresswidget.h"
#include "minion.h"
#include "quest.h"
#include "synchronizedtimer.h"
#include "reward.h"
#include <QDateTime>
#include <QGridLayout>
#include <QLabel>
#include "qmath.h"
class QuestProgressWidgetPrivate
{
public:
    QuestProgressWidgetPrivate(Quest quest, Minion minion, QuestProgressWidget* parent):p(parent),quest(quest),minion(minion),timeLabel(0){
        int questRegularTime = quest.getTime();
        Rank rankDif = quest.getRank()-minion.getRank();
        int questActualTime = questRegularTime*qPow(2,rankDif);
        questEndTime = QDateTime::currentDateTime().addMSecs(questActualTime).toMSecsSinceEpoch();
        p->connect(SynchronizedTimer::getInstance(), SIGNAL(epoch()), p, SLOT(epoch()));
    }
    Quest quest;
    Minion minion;

    qint64 questEndTime;
    QuestProgressWidget* p;
    QLabel* timeLabel;
};

QuestProgressWidget::QuestProgressWidget(Minion minion, Quest quest, QWidget *parent):
    FuriousPushButton(parent),
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
    if (!d->timeLabel) {
        QGridLayout* gridLayout = new QGridLayout();
        gridLayout->addWidget(genIconTextLabel(d->minion.getMinionResourceIcon(), d->minion.getName(),this),0,0, Qt::AlignLeft);
        gridLayout->addWidget(genIconTextLabel(d->quest.getQuestResourceIcon(), d->quest.getName(),this),0,1, Qt::AlignRight);
        d->timeLabel = new QLabel(QTime().addMSecs(d->questEndTime-current).toString(),this);
        gridLayout->addWidget(d->timeLabel, 1, 0, 1, 2, Qt::AlignHCenter);
        setLayout(gridLayout);
    }
    if (current > d->questEndTime) {
        d->timeLabel->setText(QString("Claim rewards!"));
        setEnabled(true);
    } else {
        d->timeLabel->setText(QTime().addMSecs(d->questEndTime-current).toString());
    }
}

void QuestProgressWidget::onClicked()
{
    Reward::rewardGold(d->minion, d->quest);
    emit questReward(d->minion);
    deleteLater();
}
