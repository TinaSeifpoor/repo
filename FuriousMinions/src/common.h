#ifndef COMMON_H
#define COMMON_H
#include <QHash>
class QStringList;
class QString;
class QColor;
class QWidget;
class QLabel;
class Minion;
class Quest;
enum AffinityTypes {
    Base    = 0,
    Air     = 1,
    Earth   = 2,
    Water   = 4,
    Fire    = 8,
    Death   = 16,
    Nature  = 32
};
QList<AffinityTypes> allAffinityList();
QString affinityIconString(AffinityTypes affinity);

unsigned numDigits(const unsigned n);
QList<AffinityTypes> genAffinities(int seed);

double genValue(int seed);
int genTime(int seed);
QColor affinityToColor(QList<AffinityTypes> affinityList);
QColor affinityToColor(AffinityTypes affinity);
QStringList affinityStringList(QList<AffinityTypes> affinityList);
QString affinityString(AffinityTypes affinity);
AffinityTypes affinityFromString(QString string);
typedef quint64 GoldCurrency;

typedef quint64 Power;
typedef int Rank;
const int rankConstant=-2;

QString coolNumericFormat(double number);
QLabel* genIconTextLabel(QString iconText, QString text, QWidget* parent);
QLabel* genAffinityLabel(Minion minion, AffinityTypes type, QWidget* parent);
QLabel* genAffinityLabel(Quest quest, AffinityTypes type, QWidget* parent);




#endif // COMMON_H

