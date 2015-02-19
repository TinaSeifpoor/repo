#ifndef QUEST_H
#define QUEST_H
#include <QExplicitlySharedDataPointer>
#include "common.h"
class QuestData;
class Quest
{
public:
    Quest(const Quest &other);
    explicit Quest(int seed);
    explicit Quest();
    ~Quest();
    int getTime() const;
    int getValue() const;
    Affinities getAffinities() const;
    QString getText() const;
    void reset();
    void setQuestTrigger(QObject* obj, const char *member);

private:
    QExplicitlySharedDataPointer<QuestData> __data;
};

#endif // QUEST_H
