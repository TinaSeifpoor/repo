#ifndef REWARD_H
#define REWARD_H
class Minion;
class Quest;
class RewardData;
#include <QExplicitlySharedDataPointer>
class Reward
{
public:
    Reward(const Reward &other);
    explicit Reward(Minion minion, Quest quest);
    ~Reward();
    double getReward() const;
    Minion getMinion() const;
    Quest getQuest() const;

private:
    QExplicitlySharedDataPointer<RewardData> __data;
};
#endif // REWARD_H
