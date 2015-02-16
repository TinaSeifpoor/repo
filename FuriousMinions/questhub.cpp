#include "questhub.h"
#include <QGridLayout>
#include "questwidget.h"
QuestHub::QuestHub(QWidget *parent,int nRows, int nCols):__nRows(nRows), __nCols(nCols), QWidget(parent)
{
    QGridLayout* gridLayout = new QGridLayout;
    for (int row = 0; row < nRows; ++row)
        for (int col=0; col<nCols; ++col)
            gridLayout->addWidget(QuestWidget::genQuest(this),row,col);
    setLayout(gridLayout);
}

QuestHub::~QuestHub()
{

}

