#include "questselectionwidget.h"
#include <QTimer>
#include <QGridLayout>
#include <QLabel>
void QuestSelectionWidget::resetUI()
{
    QGridLayout* gridLayout = new QGridLayout();
    int nAffinities = allAffinityList().count()+1;
    int nFirstHalfAffinities = nAffinities/2;
    int nSecondHalfAffinities = nAffinities-nFirstHalfAffinities;
    gridLayout->addWidget(genIconTextLabel(__quest.getQuestResourceIcon(), __quest.getName(),this),0,0,1,nFirstHalfAffinities);
    int i=0;
//    gridLayout->addWidget(genAffinityLabel(__quest,Base,this),1,i++,1,1);
    foreach(AffinityTypes type, allAffinityList())
        gridLayout->addWidget(genAffinityLabel(__quest,type,this),1,i++,1,1);
    gridLayout->addWidget(new QLabel(__quest.getTimeText(),this),0,nFirstHalfAffinities,1,nSecondHalfAffinities, Qt::AlignRight);
    setLayout(gridLayout);
}

QuestSelectionWidget::QuestSelectionWidget(Quest quest, QWidget *parent) : FuriousPushButton(parent), __quest(quest)
{
    resetUI();
}

QuestSelectionWidget::~QuestSelectionWidget()
{

}

void QuestSelectionWidget::reset()
{
}

Quest QuestSelectionWidget::getQuest() const
{
    return __quest;
}

QVariantHash QuestSelectionWidget::toHash() const
{
    return __quest.toHash();
}

void QuestSelectionWidget::onResetTimerFinished()
{
    resetUI();
}

