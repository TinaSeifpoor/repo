#ifndef MINIONHUB_H
#define MINIONHUB_H

#include <QWidget>
#include "minion.h"
class MinionSelectionWidget;
class QPushButton;
class MinionHub : public QWidget
{
    Q_OBJECT
    QPushButton* buyMinion;
public:
    explicit MinionHub(QWidget *parent = 0);
    MinionSelectionWidget *getMinionSelectionWidget();
    void addMinionSelectionWidget(MinionSelectionWidget* msw);
public slots:
    void minionBought();
    void addMinion(Minion minion);
};

#endif // MINIONHUB_H
