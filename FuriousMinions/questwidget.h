#ifndef QUESTWIDGET_H
#define QUESTWIDGET_H

#include <QCheckBox>
#include "affiniteetemplate.h"
class QuestWidget : public QCheckBox, protected AffiniteeTemplate
{
    Q_OBJECT
    explicit QuestWidget(QWidget *parent = 0);
    int __questValue;
    int __time;
    virtual void set(int seed);
public:
    static QuestWidget* genQuest(QWidget *parent=0);
    ~QuestWidget();
    void reset();

signals:

public slots:
    void onResetTimerFinished();
};

#endif // QUESTWIDGET_H
