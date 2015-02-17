#ifndef QUESTHUB_H
#define QUESTHUB_H

#include <QWidget>
#include "quest.h"
class QuestHub : public QWidget
{
    Q_OBJECT
    int __nRows;
    int __nCols;
public:
    explicit QuestHub(QWidget *parent = 0,int nRows=6, int nCols=4);
    ~QuestHub();
    QList<Quest> selectedQuests() const;
};

#endif // QUESTHUB_H
