#ifndef MINIONSELECTIONWIDGET_H
#define MINIONSELECTIONWIDGET_H

#include "furiouspushbutton.h"
#include "minion.h"

class MinionSelectionWidget : public FuriousPushButton
{
    Q_OBJECT
    Minion __mt;
public:
    explicit MinionSelectionWidget(Minion mt, QWidget *parent = 0);
    ~MinionSelectionWidget();
    Minion getMinion() const;
public slots:
    void minionNotification();
};

#endif // MINIONSELECTIONWIDGET_H
