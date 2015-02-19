#ifndef MINIONHUB_H
#define MINIONHUB_H

#include <QWidget>
class Minion;
class MinionSelectionWidget;
class MinionHub : public QWidget
{
    Q_OBJECT
public:
    explicit MinionHub(QWidget *parent = 0);
    MinionSelectionWidget *getMinionSelectionWidget();
    void addMinion(Minion minion);
    void addMinionSelectionWidget(MinionSelectionWidget* msw);
public slots:
    void minionBought();
};

#endif // MINIONHUB_H
