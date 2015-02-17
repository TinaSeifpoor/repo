#ifndef MINIONSELECTIONWIDGET_H
#define MINIONSELECTIONWIDGET_H

#include <QCheckBox>
#include "minion.h"

class MinionSelectionWidget : public QCheckBox
{
    Q_OBJECT
    Minion __mt;
public:
    explicit MinionSelectionWidget(Minion mt, QWidget *parent = 0);
    Minion getMinion() const;
};

#endif // MINIONSELECTIONWIDGET_H
