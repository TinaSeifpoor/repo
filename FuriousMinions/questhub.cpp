#include "questhub.h"
#include <QGridLayout>
#include "questselectionwidget.h"
QuestHub::QuestHub(QWidget *parent): QWidget(parent)
{
    setLayout(new QGridLayout());
}

QuestHub::~QuestHub()
{

}

void QuestHub::addQuest(Quest quest)
{
    layout()->addWidget(new QuestSelectionWidget(quest,this));
}

Quest QuestHub::getQuest()
{
    foreach(QuestSelectionWidget* qsw,findChildren<QuestSelectionWidget*>())
        if (qsw->isChecked()) {
            Quest quest = qsw->getQuest();
            qsw->reset();
            return quest;
        }
    return Quest(-1);
}

