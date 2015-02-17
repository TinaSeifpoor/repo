#include "questselectionwidget.h"
#include <QTimer>
void QuestSelectionWidget::resetUI()
{
    setCheckable(true);
    setText(QString("Time: %1 Affinities: (%2)").arg(__quest.getTime()/1000).arg(affinityStringList(__quest.getAffinities()).join(", ")));
}

QuestSelectionWidget::QuestSelectionWidget(Quest quest, QWidget *parent) : QCheckBox(parent), __quest(quest)
{
    resetUI();
}

QuestSelectionWidget::~QuestSelectionWidget()
{

}

void QuestSelectionWidget::reset()
{
    setText(QString("Resetting quest..."));
    QTimer::singleShot(600, this, SLOT(onResetTimerFinished()));
    setCheckable(false);
}

Quest QuestSelectionWidget::getQuest() const
{
    return __quest;
}

void QuestSelectionWidget::onResetTimerFinished()
{
    __quest.reset();
    resetUI();
}

