#ifndef QUEST_H
#define QUEST_H
#include <QExplicitlySharedDataPointer>
#include "common.h"
class QuestData;
class QPixmap;
class QObject;
#include <QVariantHash>
class Quest
{
public:
    Quest(const Quest &other);
    explicit Quest(int seed, Rank rank);
    explicit Quest(Rank rank=1);
    explicit Quest(QuestData* data);
    ~Quest();
    int getTime() const;
    Power getAffinityPower(AffinityTypes type) const;
    QString getName() const;
    QString getTimeText() const;
    QString getQuestResourceIcon() const;
    Rank getRank() const;
    void reset();
    void setQuestTrigger(QObject* obj, const char *member);
    QList<AffinityTypes> getAffinities() const;
    QVariantHash toHash() const;
    static Quest fromHash(QVariantHash hash);
private:
    QExplicitlySharedDataPointer<QuestData> __data;
};

#endif // QUEST_H
