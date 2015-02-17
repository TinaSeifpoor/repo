#include "minionhub.h"
#include "minionselectionwidget.h"
#include <QGridLayout>
MinionHub::MinionHub(QWidget *parent) :
    QWidget(parent)
{
    setLayout(new QGridLayout());
}

Minion MinionHub::getMinion()
{
    foreach(MinionSelectionWidget* msw,findChildren<MinionSelectionWidget*>())
        if (msw->isChecked()) {
            Minion minion = msw->getMinion();
            msw->deleteLater();
            return minion;
        }
}

void MinionHub::addMinion(Minion minion)
{
    QGridLayout* gridLayout = dynamic_cast<QGridLayout*>(layout());
    gridLayout->addWidget(new MinionSelectionWidget(minion, this));
}
