#include "globalvariables.h"
#include <QLabel>
#include <QMap>
#include <QHash>
#include <QAction>

QLabel* goldLabel=0;
GlobalVariables* gv=0;
GoldCurrency allGold;
typedef QMap<GoldCurrency, QAction*> GoldNotifierActionMap;
QHash<QObject*, QAction*> objectActionHash;
QHash<QObject*, const char*> objectMemberHash;
GoldNotifierActionMap limitNotifiers;
void updateGold() {
    if (goldLabel)
        goldLabel->setText(coolNumericFormat(allGold));
    qDebug(QString("New gold amount: %1").arg(allGold).toLatin1());
}

void setNotifierFromIt(GoldNotifierActionMap::iterator it, bool isAvailable) {
    GoldCurrency value = it.key();
    QAction* action = limitNotifiers.value(value,0);
    if (action) {
        action->setChecked(isAvailable);
        if (isAvailable)
            qDebug("Enabled!");
        else
            qDebug("Disabled!");
    }
}

GlobalVariables::GlobalVariables()
{
}

void GlobalVariables::setGoldLabel(QLabel *label)
{
    goldLabel = label;
}

GoldCurrency GlobalVariables::getRemainingGold()
{
    return allGold;
}

void GlobalVariables::addGold(GoldCurrency gold)
{
    GoldNotifierActionMap::iterator currentIt = limitNotifiers.upperBound(allGold);
    GoldNotifierActionMap::iterator targetIt  = limitNotifiers.upperBound(allGold+gold);
    while (targetIt!=currentIt) {
        setNotifierFromIt(currentIt++,true);
    }
    allGold+=gold;
    updateGold();
}

bool GlobalVariables::reduceGold(GoldCurrency gold)
{
    if (allGold>=gold) {
        GoldNotifierActionMap::iterator currentIt = limitNotifiers.upperBound(allGold);
        GoldNotifierActionMap::iterator targetIt  = limitNotifiers.upperBound(allGold-gold);
        while (targetIt!=currentIt) {
            setNotifierFromIt(currentIt--,false);
        }
        setNotifierFromIt(targetIt,false);
        allGold-=gold;
        updateGold();
        return true;
    }
    return false;
}

bool GlobalVariables::addGoldLimitNotifier(GoldCurrency threshold, QObject *obj, const char *member)
{
    QAction* objAction = new QAction(obj);
    if (objAction->connect(objAction, SIGNAL(toggled(bool)), obj, member)) {
        objAction->setObjectName(QString::number(threshold));
        limitNotifiers.insertMulti(threshold, objAction);
        objectActionHash.insert(obj, objAction);
        objectMemberHash.insert(obj, member);
        objAction->setCheckable(true);
        objAction->setChecked(allGold<threshold);
        objAction->setChecked(allGold>=threshold);
        return true;
    } else {
        objAction->deleteLater();
        return false;
    }
}

void GlobalVariables::removeGoldLimitNotifier(QObject *obj)
{
    if (objectActionHash.contains(obj)) {
        QAction* objAction = objectActionHash.take(obj);
        const char* member = objectMemberHash.take(obj);
        objAction->disconnect(obj, member);
        GoldCurrency threshold = objAction->objectName().toInt();
        QList<QAction*> actions = limitNotifiers.values(threshold);
        actions.removeAll(objAction);
        limitNotifiers.remove(threshold);
        foreach (QAction* action, actions)
            limitNotifiers.insertMulti(threshold, action);
        objAction->deleteLater();
    }
}
