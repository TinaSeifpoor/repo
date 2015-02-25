#include "perktemplate.h"
using namespace Perks;
const QList<PerkType> allPerks = QList<PerkType>()
<< MinionGoldGainFactor
<< ChanceForInstantQuest
<< ChanceForMoreQuestReward
<< AmountForMoreQuestReward;

#  define FOREACHPERK(variable)\
foreach(Perks variable, allPerks)

PerkTemplate::PerkTemplate()
{
    FOREACHPERK(perk)
        r.insert(perk, 0);
}

PerkTemplate::~PerkTemplate()
{

}

void PerkTemplate::setRank(PerkType perk, Rank endRank)
{
    r.insert(perk, endRank);
}

bool isChance(PerkType perk) {
    return (perk==ChanceForInstantQuest || perk==ChanceForMoreQuestReward);
}

PerkTemplate PerkTemplate::operator +(const PerkTemplate &other)
{
    PerkTemplate out;
    FOREACHPERK(perk) {
        out.setRank(perk, rank(perk)+other.rank(perk));
        qDebug("test");
    }
    return out;
}

PerkTemplate PerkTemplate::unite(QList<const PerkTemplate> &perkList)
{
    PerkTemplate<Type> out;
    out.setValue(1);
    foreach (const PerkTemplate &other, perkList)
        out = out + other;
    return out;
}
