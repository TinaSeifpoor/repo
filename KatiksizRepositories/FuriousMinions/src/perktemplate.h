#ifndef PERKTEMPLATE_H
#define PERKTEMPLATE_H
#include <QHash>
#include "common.h"
namespace Perks {

class PerkTemplate
{
    QHash<PerkType, Rank> r;
public:
    PerkTemplate();
    ~PerkTemplate();
    void addRank(PerkType perk, Rank addRank=1);
    void setRank(PerkType perk, Rank endRank);
    Rank rank(PerkType perk) const;
    double value(PerkType perk) const;
    const PerkTemplate& operator +(const PerkTemplate &other);
    static PerkTemplate unite(QList<PerkTemplate> &perkList);
    bool minionChanceForPerk();
};
}
#endif // PERKTEMPLATE_H
