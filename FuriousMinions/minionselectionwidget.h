#ifndef MINIONSELECTIONWIDGET_H
#define MINIONSELECTIONWIDGET_H

#include <QCheckBox>
#include "miniontemplate.h"

class MinionSelectionWidget : public QCheckBox
{
    Q_OBJECT
    Minion __mt;
public:
    explicit MinionSelectionWidget(Minion mt, QWidget *parent = 0);
    void getMinion(Minion mt);
};

#endif // MINIONSELECTIONWIDGET_H
