#include "questprogresshub.h"
#include <QGridLayout>
#include "questprogresswidget.h"
#include "minion.h"
#include "quest.h"
QuestProgressHub::QuestProgressHub(QWidget *parent) : QWidget(parent)
{
    setLayout(new QGridLayout(this));
    layout()->addItem(new QSpacerItem(0,0,QSizePolicy::Preferred, QSizePolicy::Expanding));
}

QuestProgressHub::~QuestProgressHub()
{

}

void QuestProgressHub::startQuest(Minion minion, Quest quest)
{
    QuestProgressWidget* qpw = new QuestProgressWidget(minion,quest,this);
    QLayoutItem* item = layout()->takeAt(layout()->count()-1);
    if (layout()->isEmpty())
        layout()->addWidget(qpw);
    else {
        QList<QuestProgressWidget*> qpwList;
        while (!layout()->isEmpty()) {
            if (QuestProgressWidget* qpwC = dynamic_cast<QuestProgressWidget*>(layout()->takeAt(layout()->count()-1)->widget())) {
                if (qpwC->questEndTime()> qpw->questEndTime()) {
                    qpwList << qpwC;
                } else {
                    qpwList << qpw << qpwC;
                    break;
                }
            }
        }
        if (layout()->isEmpty())
            qpwList << qpw;
        while (!qpwList.isEmpty())
            layout()->addWidget(qpwList.takeLast());
    }
    layout()->addItem(item);
    connect (qpw, SIGNAL(questReward(Minion)), SIGNAL(questComplete(Minion)));
}

