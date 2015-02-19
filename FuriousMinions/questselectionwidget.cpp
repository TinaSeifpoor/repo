#include "questselectionwidget.h"
#include <QTimer>
void QuestSelectionWidget::resetUI()
{
    setCheckable(true);
    setIcon(QIcon(__quest.getPixmap()));
    setIconSize(__quest.getPixmap().size());
}

QuestSelectionWidget::QuestSelectionWidget(Quest quest, QWidget *parent) : QPushButton(parent), __quest(quest)
{
    setCheckable(true);
    setAutoExclusive(true);
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

