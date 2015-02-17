#ifndef MINION_H
#define MINION_H

#include <QExplicitlySharedDataPointer>
#include "common.h"
class MinionData;
class Minion
{
public:
    Minion(const Minion &other);
    explicit Minion(int seed);
    explicit Minion();
    ~Minion();
    QString getName() const;
    Affinities getAffinities() const;
private:
    QExplicitlySharedDataPointer<MinionData> __data;
};
#endif // MINION_H
