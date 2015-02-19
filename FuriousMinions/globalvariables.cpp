#include "globalvariables.h"
#include <QLabel>
#include <QMap>
#include <QTimer>

QLabel* goldLabel=0;
GlobalVariables* gv=0;
GoldCurrency allGold;
typedef QMap<GoldCurrency, QTimer*> GoldNotifier;
GoldNotifier limitNotifiers;
void updateGold() {
    if (goldLabel)
        goldLabel->setText(QString::number(allGold));
}

GlobalVariables::GlobalVariables()
{
}

void GlobalVariables::setGoldLabel(QLabel *label)
{
    goldLabel = label;
}

qint64 GlobalVariables::getRemainingGold()
{
    return allGold;
}

void GlobalVariables::addGold(GoldCurrency gold)
{
    GoldNotifier::iterator currentIt = limitNotifiers.upperBound(allGold);
    GoldNotifier::iterator targetIt  = limitNotifiers.lowerBound(gold+allGold);
    while (targetIt!=currentIt) {
        currentIt.value()->start();
        currentIt++;
    }
    targetIt.value()->start();
    allGold+=gold;
    updateGold();
}

bool GlobalVariables::reduceGold(GoldCurrency gold)
{
    if (allGold>=gold) {
        GoldNotifier::iterator currentIt = limitNotifiers.lowerBound(allGold);
        GoldNotifier::iterator targetIt  = limitNotifiers.upperBound(gold-allGold);
        while (targetIt!=currentIt) {
            currentIt.value()->start();
            currentIt--;
        }
        targetIt.value()->start();
        allGold-=gold;
        updateGold();
        return true;
    }
    return false;
}

void GlobalVariables::addGoldLimitNotifier(GoldCurrency threshold, QObject *obj, const char *member)
{
    QObject::connect(limitNotifiers.value(threshold, new QTimer()), SIGNAL(timeout()), obj, member);
}
