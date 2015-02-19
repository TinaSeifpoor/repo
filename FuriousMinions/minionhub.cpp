#include "minionhub.h"
#include "minionselectionwidget.h"
#include <QGridLayout>
QString buyMinionText("Buy minion (%1 gold)");
MinionHub::MinionHub(QWidget *parent) :
    QWidget(parent)
{
    setLayout(new QGridLayout());
    QPushButton* buyMinion = new QPushButton(this);
    buyMinion->setObjectName("BuyMinionButton");
}

MinionSelectionWidget* MinionHub::getMinionSelectionWidget()
{
    foreach (MinionSelectionWidget* msw, findChildren<MinionSelectionWidget*>()) {
        if (msw->isChecked()) {
            return msw;
        }
    }
    return 0;
}
void MinionHub::addMinion(Minion minion)
{
    addMinionSelectionWidget(new MinionSelectionWidget(minion, this));
}

void MinionHub::addMinionSelectionWidget(MinionSelectionWidget *msw)
{
    msw->setParent(this);
    layout()->addWidget(msw);
}
