#include "questhub.h"
#include <QGridLayout>
#include "questselectionwidget.h"
QuestHub::QuestHub(QWidget *parent): QWidget(parent)
{
    setLayout(new QGridLayout());
    layout()->setMargin(4);
    layout()->addItem(new QSpacerItem(0,0,QSizePolicy::Preferred, QSizePolicy::Expanding));
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
    QLayoutItem* item = layout()->takeAt(layout()->count()-1);
    layout()->addWidget(qsw);
    layout()->addItem(item);
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
