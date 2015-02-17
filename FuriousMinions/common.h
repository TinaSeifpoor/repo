#ifndef COMMON_H
#define COMMON_H
#include <QFlags>
#include <QStringList>
class QColor;
enum AffinityTypes {
    Air     = 1,
    Earth   = 2,
    Water   = 4,
    Fire    = 8,
    Death   = 16,
    Nature  = 32
};
Q_DECLARE_FLAGS(Affinities, AffinityTypes)

unsigned numDigits(const unsigned n);
Affinities genAffinities(int seed);

double genValue(int seed);
int genTime(int seed);

QColor affinityToColor(Affinities type);
QStringList affinityStringList(Affinities type);


#endif // COMMON_H

