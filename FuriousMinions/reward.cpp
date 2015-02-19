#include "reward.h"
#include "minion.h"
#include "quest.h"
class RewardData : public QSharedData
{
public:
    RewardData(Minion minion, Quest quest):__quest(quest),__minion(minion){}
    Quest __quest;
    Minion __minion;
    double calculatePower() {
        Affinities questAffinities  = __quest.getAffinities();
        QList<AffinityTypes> questAffinityList = convertToAffinityList(questAffinities);
        double power = __minion.getBasePower();
        foreach (AffinityTypes affinity, questAffinityList)
            power+= __minion.getAffinityPower(affinity);
        return power;
    }
};

Reward::Reward(const Reward &other) : __data(other.__data)
{

}

Reward::Reward(Minion minion, Quest quest) : __data(new RewardData(minion,quest))
{

}

Reward::~Reward()
{

}

double Reward::getReward() const
{
    return __data->__quest.getValue()*__data->calculatePower();
}

Minion Reward::getMinion() const
{
    return __data->__minion;
}

Quest Reward::getQuest() const
{
    return __data->__quest;
}
