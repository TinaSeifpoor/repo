#ifndef REWARD_H
#define REWARD_H
#include "minion.h"
#include "quest.h"
class RewardData;
#include <QExplicitlySharedDataPointer>
class Reward
{
public:
    Reward(const Reward &other);
    explicit Reward(Minion minion, Quest quest);
    ~Reward();
    double getExperienceReward() const;

private:
    QExplicitlySharedDataPointer<RewardData> __data;
};
#endif // REWARD_H
