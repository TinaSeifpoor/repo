#include "quest.h"
#include "affiniteetemplate.h"

#include "qmath.h"
class QuestData : public AffiniteeTemplate
{
public:
    int __questValue;
    int __questTime;
    virtual void set(int seed)
    {
        AffiniteeTemplate::set(seed);
        __questValue = this->genValue(get());
        __questTime = this->genTime(get());
    }
private:
    double genValue(int seed) const
    {
        return seed%500000;
    }

    int genTime(int seed) const
    {
        int minTime = 60000;
        int maxTime = 300000;
        return minTime + seed%(maxTime-minTime);
    }
};

Quest::Quest(const Quest &other) : __data(other.__data)
{

}

Quest::Quest(int seed) : __data(new QuestData())
{
    __data->set(seed);
}

Quest::~Quest()
{

}

Quest::Quest():__data(new QuestData()){
    __data->set(qrand());
}

int Quest::getTime() const
{
    return __data->__questTime;
}

int Quest::getValue() const
{
    return __data->__questValue;
}


Affinities Quest::getAffinities() const
{
    return __data->getAffinities();
}

void Quest::reset()
{
    __data.detach();
    __data->set(qrand());
}
