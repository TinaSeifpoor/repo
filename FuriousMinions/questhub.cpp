#include "questhub.h"
#include <QGridLayout>
#include "questselectionwidget.h"
QuestHub::QuestHub(QWidget *parent,int nRows, int nCols):__nRows(nRows), __nCols(nCols), QWidget(parent)
{
    QGridLayout* gridLayout = new QGridLayout;
    for (int row = 0; row < nRows; ++row)
        for (int col=0; col<nCols; ++col)
            gridLayout->addWidget(new QuestSelectionWidget(Quest(),this),row,col);
    setLayout(gridLayout);
}

QuestHub::~QuestHub()
{

}

QList<Quest> QuestHub::selectedQuests() const
{
        QList<Quest> selectedQuests ;
        foreach(QuestSelectionWidget* qsw,findChildren<QuestSelectionWidget*>())
            if (qsw->isChecked())
                selectedQuests << qsw->getQuest();
        return selectedQuests ;
}

