#ifndef QUESTWIDGET_H
#define QUESTWIDGET_H

#include <QCheckBox>
#include "common.h"
class QuestWidget : public QCheckBox
{
    Q_OBJECT
    explicit QuestWidget(QWidget *parent = 0);
    int __questValue;
    int __time;
    Affinities __questAffinities;
    int __seed;
    void set(int seed);
public:
    static QuestWidget* genQuest(QWidget *parent=0);
    ~QuestWidget();
    void reset();

signals:

public slots:
    void onResetTimerFinished();
};

#endif // QUESTWIDGET_H
