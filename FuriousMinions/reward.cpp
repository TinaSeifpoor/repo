#include "reward.h"
#include "minion.h"
#include "quest.h"
#include "globalvariables.h"
double calculatePower(Minion minion, Quest quest) {
    QList<AffinityTypes> questAffinityList  = quest.getAffinities();
    Power power=0;
    foreach (AffinityTypes affinity, questAffinityList)
        power+= minion.getAffinityPower(affinity) * quest.getAffinityPower(affinity);
    return power;
}
void Reward::rewardGold(Minion minion, Quest quest)
{
    GlobalVariables::addGold(calculatePower(minion,quest));
}
