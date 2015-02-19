#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H
#include <QtGlobal>
class QLabel;
class QObject;
typedef qint64 GoldCurrency;
class GlobalVariables
{
    GlobalVariables();
public:
    static void setGoldLabel(QLabel *label);
    static GoldCurrency getRemainingGold();
    static void addGold(GoldCurrency gold);
    static bool reduceGold(GoldCurrency gold);
    static void addGoldLimitNotifier(GoldCurrency threshold, QObject* obj, const char* member);
};

#endif // GLOBALVARIABLES_H
