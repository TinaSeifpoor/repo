#include "minionselectionwidget.h"

MinionSelectionWidget::MinionSelectionWidget(Minion mt, QWidget *parent) :
    QCheckBox(parent),
    __mt(mt)
{
    setText(__mt.getName());
}

Minion MinionSelectionWidget::getMinion() const
{
    return __mt;
}
