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
    addQuestSelectionWidget(new QuestSelectionWidget(quest,this));
}

void QuestHub::addQuestSelectionWidget(QuestSelectionWidget *qsw)
{
    qsw->setParent(this);
    layout()->addWidget(qsw);
}

QuestSelectionWidget *QuestHub::getQuestSelectionWidget()
{
    foreach (QuestSelectionWidget* qsw, findChildren<QuestSelectionWidget*>()) {
        if (qsw->isChecked()) {
            return qsw;
        }
    }
    return 0;
}

