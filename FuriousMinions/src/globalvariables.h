#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H
#include <QtGlobal>
#include "common.h"
class QLabel;
class QObject;
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
};

#endif // GLOBALVARIABLES_H
