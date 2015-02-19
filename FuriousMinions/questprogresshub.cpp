#include "questprogresshub.h"
#include <QGridLayout>
#include "questprogresswidget.h"
#include "minion.h"
#include "quest.h"
QuestProgressHub::QuestProgressHub(QWidget *parent) : QWidget(parent)
{
    setLayout(new QGridLayout(this));
}

QuestProgressHub::~QuestProgressHub()
{

}

void QuestProgressHub::startQuest(Minion minion, Quest quest)
{
    QuestProgressWidget* qpw = new QuestProgressWidget(minion,quest,this);
    layout()->addWidget(qpw);
    connect (qpw, SIGNAL(questReward(Reward)), SIGNAL(questComplete(Reward)));
}

