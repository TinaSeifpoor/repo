#include "globalvariables.h"
#include <QLabel>
#include <QMap>
#include <QHash>
#include <QAction>
#include "qmath.h"
GoldCurrency allGold=0;
GoldCurrency allGoldAcquiredSinceAscension=0;
QHash<Rank, int> questCounterHash;
int minionCounter=0;
int questCounter=0;



GlobalVariables* gv=0;
QLabel* goldLabel=0;

QObject* nextLevelNotifierObject=0;
const char* nextLevelNotifierMember=0;
typedef QMap<GoldCurrency, QAction*> GoldNotifierActionMap;
QHash<QObject*, QAction*> objectActionHash;
QHash<QAction*, GoldCurrency> actionThresholdHash;
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
    allGoldAcquiredSinceAscension+=gold;
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
        actionThresholdHash.insert(objAction, threshold);
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
        GoldCurrency threshold = actionThresholdHash.value(objAction);
        QList<QAction*> actions = limitNotifiers.values(threshold);
        actions.removeAll(objAction);
        limitNotifiers.remove(threshold);
        foreach (QAction* action, actions)
            limitNotifiers.insertMulti(threshold, action);
        objAction->deleteLater();
    }
}

QVariantHash GlobalVariables::toHash()
{
    QVariantHash globalVariablesHash;
    globalVariablesHash.insert("AllGold", allGold);
    globalVariablesHash.insert("AllGoldSinceAscension", allGoldAcquiredSinceAscension);
    globalVariablesHash.insert("MinionCount", minionCounter);
    QVariantHash questCounterVariantHash;
    foreach (Rank rank, questCounterHash.keys())
        questCounterVariantHash.insert(QString::number(rank), questCounterHash.value(rank));
    globalVariablesHash.insert("QuestCounterHash", questCounterVariantHash);
    return globalVariablesHash;
}

void GlobalVariables::fromHash(QVariantHash hash)
{
    allGoldAcquiredSinceAscension = hash.value("AllGoldSinceAscension",300).toDouble();
    allGold = 0;
    addGold(hash.value("AllGold",300).toDouble());
    minionCounter = hash.value("MinionCount").toInt();
    QVariantHash questCounterVariantHash = hash.value("QuestCounterHash").toHash();
    questCounterVariantHash.clear();
    foreach (QString rankKey, questCounterVariantHash.keys())
        questCounterHash.insert(rankKey.toInt(), questCounterVariantHash.value(rankKey).toInt());

}

void GlobalVariables::addMinion(Rank r)
{
    minionCounter++;
}
#include <QTimer>
void GlobalVariables::addQuest(Rank r)
{
    questCounterHash[r]++;
    if (questCounterHash[r]==10)
       QTimer::singleShot(0, nextLevelNotifierObject, nextLevelNotifierMember);
    questCounter++;
}

bool GlobalVariables::calculateMinionRank(Rank currentRank, int nQuests)
{
    int expectedCount = nQuests/(qPow(2,currentRank));
    int chance = qMin(qMax(expectedCount,-rankConstant)+rankConstant+1,10);
    if (qrand()%10<chance)
        return true;
    else
        return false;
}

int GlobalVariables::minionCount()
{
    return minionCounter;
}

GoldCurrency GlobalVariables::nextMinionGold()
{
    return qPow(20,minionCount()+1)*(minionCount()+1)+50;
}

void GlobalVariables::setNextLevelNotifier(QObject *obj, const char *member)
{
    nextLevelNotifierObject=obj;
    nextLevelNotifierMember=member;
}

int GlobalVariables::questCount(Rank rank)
{
    return questCounterHash.value(rank);
}


