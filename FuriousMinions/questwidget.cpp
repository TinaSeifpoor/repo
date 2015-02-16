#include "questwidget.h"
#include <QCheckBox>
#include <QTimer>
QuestWidget::QuestWidget(QWidget *parent) : QCheckBox(parent)
{
    setCheckable(true);
}

void QuestWidget::set(int seed)
{
    AffiniteeTemplate::set(seed);
    __questValue = genValue(get());
    __time = qBound(60000,__questValue*1000,300000);
    setText(QString("Time: %1 Affinities: (%2)").arg(__time/1000).arg(affinityStringList(getAffinities()).join(", ")));
}

QuestWidget *QuestWidget::genQuest(QWidget *parent)
{
    QuestWidget* qw = new QuestWidget(parent);
    qw->set(qrand());
    return qw;
}

QuestWidget::~QuestWidget()
{

}

void QuestWidget::reset()
{
    setText(QString("Resetting quest..."));
    QTimer::singleShot(600, this, SLOT(onResetTimerFinished()));
}

void QuestWidget::onResetTimerFinished()
{
    set(qrand());
}

