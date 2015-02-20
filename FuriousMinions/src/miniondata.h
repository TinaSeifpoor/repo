#ifndef MINIONDATA_H
#define MINIONDATA_H
#include "affiniteetemplate.h"

class MinionData : public AffiniteeTemplate
{
    QString __minionName;
    QList<QObject*> objsToNotify;
    QList<const char*> membersToNotify;
    void setName();
    virtual QHash<AffinityTypes, Power> setPowers(QList<AffinityTypes> types);
    Rank __rank;

public:
    MinionData();
    ~MinionData();
    Rank getRank() const;

    QString getMinionResourceIcon() const;
    virtual void set(int seed);
    QString minionName() const;
    void addObj(QObject* obj, const char* member);
    void removeObj(QObject* obj);
    void notify() const;
    static int minionCount(Rank __rank);
    static int minionCount();
    static GoldCurrency nextMinionGold();
    static Rank nextRank();
};
#endif // MINIONDATA_H
