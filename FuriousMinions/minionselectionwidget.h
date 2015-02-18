#ifndef MINIONSELECTIONWIDGET_H
#define MINIONSELECTIONWIDGET_H

#include <QPushButton>
#include "minion.h"

class MinionSelectionWidget : public QPushButton
{
    Q_OBJECT
    Minion __mt;
public:
    explicit MinionSelectionWidget(Minion mt, QWidget *parent = 0);
    Minion getMinion() const;
public slots:
    void minionNotification();
};

#endif // MINIONSELECTIONWIDGET_H
