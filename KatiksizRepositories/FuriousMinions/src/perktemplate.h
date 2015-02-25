#ifndef PERKTEMPLATE_H
#define PERKTEMPLATE_H
#include <QHash>
#include "common.h"
namespace Perks {
enum PerkType {
    MinionGoldGainFactor,
    ChanceForInstantQuest,
    ChanceForMoreQuestReward,
    AmountForMoreQuestReward
};
class PerkTemplate
{
    QHash<PerkType, Rank> r;

public:
    explicit PerkTemplate();
    virtual ~PerkTemplate();
    virtual void addRank(PerkType perk);
    virtual void setRank(PerkType perk, Rank endRank);
    virtual Rank rank(PerkType perk) const;
    virtual double value(PerkType perk) const;
    virtual PerkTemplate operator +(const PerkTemplate &other);
    static PerkTemplate unite(QList<const PerkTemplate> &perkList);
};
}
#endif // PERKTEMPLATE_H
