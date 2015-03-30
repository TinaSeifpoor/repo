#include "perktemplate.h"
using Perks::PerkType;
using Perks::PerkTemplate;
const QList<PerkType> allPerks = QList<PerkType>()
<< Perks::MinionGoldGainFactor
<< Perks::ChanceForInstantQuest
<< Perks::ChanceForMoreQuestReward
<< Perks::AmountForMoreQuestReward
<< Perks::MinionUpgradeFactor
<< Perks::ChanceForDoubleLevelUp;

#  define FOREACHPERK(variable) foreach(Perks::PerkType variable, allPerks)

PerkTemplate::PerkTemplate()
{
    FOREACHPERK(perk)
        r.insert(perk, 0);
}

PerkTemplate::~PerkTemplate()
{

}

void PerkTemplate::addRank(Perks::PerkType perk, Rank addRank)
{
    r[perk]+= addRank;
}

void PerkTemplate::setRank(PerkType perk, Rank endRank)
{
    r.insert(perk, endRank);
}

Rank PerkTemplate::rank(Perks::PerkType perk) const
{
    return r.value(perk);
}

bool isChance(PerkType perk) {
    return (perk==Perks::ChanceForInstantQuest ||
            perk==Perks::ChanceForMoreQuestReward ||
            perk==Perks::ChanceForDoubleLevelUp);
}

const Perks::PerkTemplate &PerkTemplate::operator +(const PerkTemplate &other)
{
    FOREACHPERK(perk) {
        this->addRank(perk, other.rank(perk));
        qDebug("test");
    }
    return *this;
}

PerkTemplate PerkTemplate::unite(QList<PerkTemplate> &perkList)
{
    PerkTemplate out;
    foreach (const PerkTemplate &other, perkList)
        FOREACHPERK(perk)
            out.addRank(perk, other.rank(perk));
    return out;
}



bool PerkTemplate::minionChanceForPerk()
{
    int totalRanks=0;
    FOREACHPERK(perk)
            totalRanks+=rank(perk);
    if(totalRanks==0)
        return true;
    else
        return !(qrand()%totalRanks);
}

