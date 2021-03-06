#ifndef MINIONDATA_H
#define MINIONDATA_H
#include "affiniteetemplate.h"
#include "perktemplate.h"
#include <QVariantHash>
class MinionData : public AffiniteeTemplate
{
    QString __minionName;
    QList<QObject*> objsToNotify;
    QList<const char*> membersToNotify;
    void setName();
    virtual void setPowers(QList<AffinityTypes> types);
    Rank __rank;
    Perks::PerkTemplate __minionPerks;
    int __nQuestsCompleted;
    QString __icon;

public:
    MinionData();
    ~MinionData();
    Rank getRank() const;
    QVariantHash toHash() const;
    static MinionData* fromHash(QVariantHash hash);
    QString getMinionResourceIcon() const;
    virtual void set(int seed, bool isHidden=false);
    QString minionName() const;
    void addObj(QObject* obj, const char* member);
    void removeObj(QObject* obj);
    void notify() const;
    void questCompleted();
    GoldCurrency getGoldForNextLevel() const;
    void nextLevelPurchased(bool isFree);
};
#endif // MINIONDATA_H
