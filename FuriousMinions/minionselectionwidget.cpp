#include "minionselectionwidget.h"
#include <QGridLayout>
#include <QLabel>
MinionSelectionWidget::MinionSelectionWidget(Minion mt, QWidget *parent) :
    FuriousPushButton(parent),
    __mt(mt)
{
    int nAffinities = __mt.getAffinities().count();
    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->addWidget(new QLabel(__mt.getName(),this),0,0,1,nAffinities);
    int i=0;
    foreach(AffinityTypes type, __mt.getAffinities()) {
        QColor affinityColor = affinityToColor(type);
        gridLayout->addWidget(new QLabel(coolNumericFormat(__mt.getAffinityPower(type)),this),1,i++);
    }
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
//    setIcon(QIcon(*__mt.getPixmap()));
}
