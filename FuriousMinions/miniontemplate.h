#ifndef MINIONTEMPLATE_H
#define MINIONTEMPLATE_H
#include "affiniteetemplate.h"
class MinionTemplate;
typedef QExplicitlySharedDataPointer<MinionTemplate> Minion;
class MinionTemplate : public AffiniteeTemplate
{
    MinionTemplate();
    QString __minionName;
    virtual void set(int seed);
public:
    static Minion gen(int seed);
    QString name() const;
};

#endif // MINIONTEMPLATE_H
