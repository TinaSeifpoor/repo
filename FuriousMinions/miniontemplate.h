#ifndef MINIONTEMPLATE_H
#define MINIONTEMPLATE_H
#include "affiniteetemplate.h"
class MinionTemplate : public AffiniteeTemplate
{
    MinionTemplate();
    QString __minionName;
    virtual void set(int seed);
public:
    MinionTemplate* gen(int seed);
};

#endif // MINIONTEMPLATE_H
