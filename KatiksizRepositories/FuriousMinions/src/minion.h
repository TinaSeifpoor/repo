#ifndef MINION_H
#define MINION_H

#include <QExplicitlySharedDataPointer>
#include "common.h"
#include <QVariantHash>
class QPixmap;
class QObject;
class MinionData;
class Minion
{
public:
    Minion(const Minion &other);
    explicit Minion(int seed);
    explicit Minion();
    explicit Minion(MinionData *data);
    ~Minion();
    QString getName() const;
    Rank getRank() const;
    QString getMinionResourceIcon() const;
    QList<AffinityTypes> getAffinities() const;
    Power getAffinityPower(AffinityTypes affinity) const;
    void setMinionTrigger(QObject* obj, const char *member);
    void removeMinionTrigger(QObject* obj);
    void questComplete();
    QVariantHash toHash() const;
    static Minion fromHash(QVariantHash hash);
private:
    QExplicitlySharedDataPointer<MinionData> __data;
};
#endif // MINION_H
