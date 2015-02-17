#include "minionselectionwidget.h"

MinionSelectionWidget::MinionSelectionWidget(Minion mt, QWidget *parent) :
    QCheckBox(parent),
    __mt(mt)
{
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
