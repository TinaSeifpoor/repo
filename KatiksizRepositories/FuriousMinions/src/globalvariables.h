#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H
#include <QtGlobal>
#include "common.h"
class QLabel;
class QObject;
#include <QVariantHash>
class GlobalVariables
{
    GlobalVariables();
public:
    static void setGoldLabel(QLabel *label);
    static GoldCurrency getRemainingGold();
    static void addGold(GoldCurrency gold);
    static bool reduceGold(GoldCurrency gold);
    static bool addGoldLimitNotifier(GoldCurrency threshold, QObject* obj, const char* member);
    static void removeGoldLimitNotifier(QObject* obj);
    static QVariantHash toHash();
    static void fromHash(QVariantHash hash);
    static void addMinion(Rank r);
    static void addQuest (Rank r);
    static bool calculateMinionRank(Rank currentRank, int nQuests);
    static int minionCount();
    static GoldCurrency nextMinionGold();
    static void setNextLevelNotifier(QObject* obj, const char* member);
    static int questCount(Rank rank);
};

#endif // GLOBALVARIABLES_H
