#include "minionhub.h"
#include "minionselectionwidget.h"
#include <QGridLayout>
MinionHub::MinionHub(QWidget *parent) :
    QWidget(parent)
{
    int nRows = 3;
    int nCols = 3;
    QGridLayout* gridLayout = new QGridLayout;
    for (int row = 0; row < nRows; ++row)
        for (int col=0; col<nCols; ++col)
            gridLayout->addWidget(new MinionSelectionWidget(Minion(), this),row,col);
    setLayout(gridLayout);
}

QList<Minion> MinionHub::selectedMinions() const
{
    QList<Minion> selectedMinions;
    foreach(MinionSelectionWidget* msw,findChildren<MinionSelectionWidget*>())
        if (msw->isChecked())
            selectedMinions << msw->getMinion();
    return selectedMinions;
}
