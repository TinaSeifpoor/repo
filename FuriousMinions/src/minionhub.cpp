#include "minionhub.h"
#include "minionselectionwidget.h"
#include <QGridLayout>
#include "globalvariables.h"
#include "furiouspushbutton.h"
#include <QLabel>
#include <QGridLayout>
QString buyMinionText("New Minion %1");
MinionHub::MinionHub(QWidget *parent) :
    QWidget(parent),
    buyMinion(new FuriousPushButton(this))
{
    setLayout(new QGridLayout());
    layout()->addWidget(buyMinion);
    layout()->addItem(new QSpacerItem(0,0,QSizePolicy::Preferred, QSizePolicy::Expanding));
    connect(buyMinion, SIGNAL(clicked()), SLOT(minionBought()));
    GlobalVariables::addGoldLimitNotifier(GlobalVariables::nextMinionGold(), buyMinion, SLOT(setShown(bool)));
    buyMinion->setAutoExclusive(false);
    buyMinion->setCheckable(false);
    QLabel* goldIcon = new QLabel(buyMinion);
    goldIcon->setPixmap(QPixmap(":/icons/currency/15/goldIcon.gif"));
    goldIcon->setAlignment(Qt::AlignLeft);
    goldLabel = new QLabel(buyMinion);
    goldLabel->setText(buyMinionText.arg(coolNumericFormat(GlobalVariables::nextMinionGold())));
    goldLabel->setAlignment(Qt::AlignRight);
    QGridLayout* layout = new QGridLayout(buyMinion);
    layout->addItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Fixed),0,0);
    layout->addWidget(goldLabel,0,1);
    layout->addWidget(goldIcon,0,2);
    layout->addItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Fixed),0,3);
    buyMinion->setLayout(layout);
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
    QLayoutItem* item = layout()->takeAt(layout()->count()-1);
    layout()->addWidget(msw);
    layout()->addItem(item);
}

void MinionHub::minionBought()
{
    if (GlobalVariables::reduceGold(GlobalVariables::nextMinionGold())) {
        addMinion(Minion());
        GlobalVariables::removeGoldLimitNotifier(buyMinion);
        GlobalVariables::addGoldLimitNotifier(GlobalVariables::nextMinionGold(), buyMinion, SLOT(setShown(bool)));
        goldLabel->setText(buyMinionText.arg(coolNumericFormat(GlobalVariables::nextMinionGold())));
    }
}

QVariantHash MinionHub::toHash() const
{
    QVariantHash questProgressHubHash;
    QList<MinionSelectionWidget*> mswList = findChildren<MinionSelectionWidget*>();
    for (int i=0; i<mswList.count();++i) {
        questProgressHubHash.insert(QString::number(i),mswList.value(i)->toHash());
    }
    return questProgressHubHash;
}

void MinionHub::fromHash(QVariantHash hash)
{
    foreach (QVariant var, hash) {
        addMinionSelectionWidget(new MinionSelectionWidget(Minion::fromHash(var.toHash()),this));
    }
    GlobalVariables::removeGoldLimitNotifier(buyMinion);
    GlobalVariables::addGoldLimitNotifier(GlobalVariables::nextMinionGold(), buyMinion, SLOT(setShown(bool)));
    goldLabel->setText(buyMinionText.arg(coolNumericFormat(GlobalVariables::nextMinionGold())));
}
