#include "minionhub.h"
#include "minionselectionwidget.h"
#include <QGridLayout>
#include "globalvariables.h"
QString buyMinionText("Buy minion (%1 gold)");
MinionHub::MinionHub(QWidget *parent) :
    QWidget(parent),
    buyMinion(new QPushButton(this))
{
    setLayout(new QGridLayout());
    layout()->addWidget(buyMinion);
    layout()->addItem(new QSpacerItem(0,0,QSizePolicy::Preferred, QSizePolicy::Expanding));
    connect(buyMinion, SIGNAL(pressed()), SLOT(minionBought()));
    GlobalVariables::addGoldLimitNotifier(Minion::nextMinionGold(), buyMinion, SLOT(setEnabled(bool)));
    buyMinion->setText(buyMinionText.arg(Minion::nextMinionGold()));
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
    layout()->removeWidget(buyMinion);
    QLayoutItem* item = layout()->takeAt(layout()->count()-1);
    layout()->addWidget(msw);
    layout()->addWidget(buyMinion);
    layout()->addItem(item);
}

void MinionHub::minionBought()
{
    if (GlobalVariables::reduceGold(Minion::nextMinionGold())) {
        addMinion(Minion());
        GlobalVariables::removeGoldLimitNotifier(buyMinion);
        GlobalVariables::addGoldLimitNotifier(Minion::nextMinionGold(), buyMinion, SLOT(setEnabled(bool)));
        buyMinion->setText(buyMinionText.arg(Minion::nextMinionGold()));
    }
}
