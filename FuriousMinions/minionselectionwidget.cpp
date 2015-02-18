#include "minionselectionwidget.h"

MinionSelectionWidget::MinionSelectionWidget(Minion mt, QWidget *parent) :
    QPushButton(parent),
    __mt(mt)
{
    setCheckable(true);
    setAutoExclusive(true);
    setText(__mt.getName());
    __mt.setMinionTrigger(this, SLOT(minionNotification()));
}

Minion MinionSelectionWidget::getMinion() const
{
    return __mt;
}

void MinionSelectionWidget::minionNotification()
{
    setText(__mt.getName());
}
