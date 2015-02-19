#ifndef QUEST_H
#define QUEST_H
#include <QExplicitlySharedDataPointer>
#include "common.h"
class QuestData;
class QPixmap;
class Quest
{
public:
    Quest(const Quest &other);
    explicit Quest(int seed);
    explicit Quest();
    ~Quest();
    int getTime() const;
    Power getAffinityPower(AffinityTypes type) const;
    QString getText() const;
    QPixmap getPixmap() const;
    void reset();
    void setQuestTrigger(QObject* obj, const char *member);
    QList<AffinityTypes> getAffinities() const;
private:
    QExplicitlySharedDataPointer<QuestData> __data;
};

#endif // QUEST_H
