#include "minionselectionwidget.h"
#include <QGridLayout>
#include <QLabel>
MinionSelectionWidget::MinionSelectionWidget(Minion mt, QWidget *parent) :
    FuriousPushButton(parent),
    __mt(mt)
{
    QGridLayout* gridLayout = new QGridLayout();
    int nAffinities = allAffinityList().count()+1;
    gridLayout->addWidget(genIconTextLabel(__mt.getMinionResourceIcon(), __mt.getName(),this),0,0,1,nAffinities);
    int i=0;
    gridLayout->addWidget(genAffinityLabel(__mt,Base,this),1,i++,1,1);
    foreach(AffinityTypes type, allAffinityList())
        gridLayout->addWidget(genAffinityLabel(__mt,type,this),1,i++,1,1);
    setLayout(gridLayout);
    __mt.setMinionTrigger(this, SLOT(minionNotification()));
}

MinionSelectionWidget::~MinionSelectionWidget()
{
    __mt.removeMinionTrigger(this);
}

Minion MinionSelectionWidget::getMinion() const
{
    return __mt;
}

void MinionSelectionWidget::minionNotification()
{
}
