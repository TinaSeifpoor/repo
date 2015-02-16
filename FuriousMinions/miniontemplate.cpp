#include "miniontemplate.h"

MinionTemplate::MinionTemplate()
{
}

void MinionTemplate::set(int seed)
{
    AffiniteeTemplate::set(seed);
    __minionName = QString("Seed: %1 Affinities: (%2)").arg(get()).arg(affinityStringList(getAffinities()).join(", "));
}

MinionTemplate *MinionTemplate::gen(int seed)
{
    MinionTemplate* mt = new MinionTemplate;
    mt->set(seed);
    return mt;
}
