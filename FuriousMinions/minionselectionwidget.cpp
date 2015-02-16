#include "minionselectionwidget.h"
#include "miniontemplate.h"

MinionSelectionWidget::MinionSelectionWidget(MinionTemplate* mt, QWidget *parent) :
    QCheckBox(parent),
    __mt(mt)
{
}
