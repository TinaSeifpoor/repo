#ifndef COMMON_H
#define COMMON_H
#include <QFlags>
#include <QStringList>
class QColor;
enum AffinityTypes {
    Base    = 0,
    Air     = 1,
    Earth   = 2,
    Water   = 4,
    Fire    = 8,
    Death   = 16,
    Nature  = 32
};

unsigned numDigits(const unsigned n);
QList<AffinityTypes> genAffinities(int seed);

double genValue(int seed);
int genTime(int seed);
//QList<AffinityTypes> convertToAffinityList(Affinities affinities);
QColor affinityToColor(QList<AffinityTypes> affinityList);
QColor affinityToColor(AffinityTypes affinity);
QStringList affinityStringList(QList<AffinityTypes> affinityList);
QString affinityString(AffinityTypes affinity);
typedef qint64 GoldCurrency;

typedef qint64 Power;

QString coolNumericFormat(double number);



#endif // COMMON_H

