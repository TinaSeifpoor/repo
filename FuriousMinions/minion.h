#ifndef MINION_H
#define MINION_H

#include <QExplicitlySharedDataPointer>
#include "common.h"
class QPixmap;
typedef int MinionRank;
class MinionData;
class Minion
{
public:
    Minion(const Minion &other);
    explicit Minion(int seed);
    explicit Minion();
    ~Minion();
    QString getName() const;
    QPixmap* getPixmap() const;
    QList<AffinityTypes> getAffinities() const;
    Power getAffinityPower(AffinityTypes affinity) const;
    void setMinionTrigger(QObject* obj, const char *member);
    void removeMinionTrigger(QObject* obj);
    static int totalNumberOfMinions();
    static GoldCurrency nextMinionGold();
private:
    QExplicitlySharedDataPointer<MinionData> __data;
};
#endif // MINION_H
