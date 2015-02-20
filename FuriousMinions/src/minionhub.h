#ifndef MINIONHUB_H
#define MINIONHUB_H

#include <QWidget>
#include "minion.h"
class MinionSelectionWidget;
class FuriousPushButton;
class MinionHub : public QWidget
{
    Q_OBJECT
    FuriousPushButton* buyMinion;
    QLabel* goldLabel;
public:
    explicit MinionHub(QWidget *parent = 0);
    MinionSelectionWidget *getMinionSelectionWidget();
    void addMinionSelectionWidget(MinionSelectionWidget* msw);
signals:
    void minionSelected(Minion minion);

public slots:
    void minionBought();
    void addMinion(Minion minion);
};

#endif // MINIONHUB_H
