#ifndef MINIONSELECTIONWIDGET_H
#define MINIONSELECTIONWIDGET_H

#include "furiouspushbutton.h"
#include "minion.h"
class QPushButton;
class MinionSelectionWidget : public FuriousPushButton
{
    Q_OBJECT
    Minion __mt;
    QPushButton* levelUpButton;
public:
    explicit MinionSelectionWidget(Minion mt, QWidget *parent = 0);
    static MinionSelectionWidget* fromHash(QVariantHash hash, QWidget *parent = 0);
    ~MinionSelectionWidget();
    Minion getMinion() const;
    QVariantHash toHash() const;
public slots:
    void minionNotification();
};

#endif // MINIONSELECTIONWIDGET_H
