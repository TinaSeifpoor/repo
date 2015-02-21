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

qint64 QuestProgressWidget::questEndTime() const
{
    return d->questEndTime;
}

QVariantHash QuestProgressWidget::toHash() const
{
    QVariantHash questProgressWidgetHash;
    questProgressWidgetHash.insert("Quest",d->quest.toHash());
    questProgressWidgetHash.insert("Minion",d->minion.toHash());
    questProgressWidgetHash.insert("EndTime",d->questEndTime);
    return questProgressWidgetHash;
}

QuestProgressWidget *QuestProgressWidget::fromHash(QVariantHash hash, QWidget *parent)
{
    QuestProgressWidget* qpw = new QuestProgressWidget(Minion::fromHash(hash.value("Minion").toHash()),Quest::fromHash(hash.value("Quest").toHash()),parent);
    qpw->d->questEndTime = hash.value("EndTime").toInt();
    return qpw;
}

void QuestProgressWidget::epoch()
{
    qint64 current = QDateTime::currentDateTime().toMSecsSinceEpoch();
    if (!d->timeLabel) {
        QGridLayout* gridLayout = new QGridLayout();
        gridLayout->addWidget(genIconTextLabel(d->minion.getMinionResourceIcon(), d->minion.getName(),this),0,0, Qt::AlignLeft);
        gridLayout->addWidget(genIconTextLabel(d->quest.getQuestResourceIcon(), d->quest.getName(),this),0,1, Qt::AlignRight);
        d->timeLabel = new QLabel(QTime::fromString("00:00:00:000", "hh:mm:ss:zzz").addMSecs(d->questEndTime-current).toString(),this);
        gridLayout->addWidget(d->timeLabel, 1, 0, 1, 2, Qt::AlignHCenter);
        setLayout(gridLayout);
    }
    if (current > d->questEndTime) {
        d->timeLabel->setText(QString("Claim rewards!"));
        disconnect(SynchronizedTimer::getInstance(), SIGNAL(epoch()), this, SLOT(epoch()));
        setEnabled(true);
    } else {
        d->timeLabel->setText(QTime::fromString("00:00:00:000", "hh:mm:ss:zzz").addMSecs(d->questEndTime-current).toString("hh:mm:ss"));
    }
}

void QuestProgressWidget::onClicked()
{
    Reward::rewardGold(d->minion, d->quest);
    d->minion.questComplete();
    emit questReward(d->minion);
    emit questComplete(d->quest);
    deleteLater();
}
