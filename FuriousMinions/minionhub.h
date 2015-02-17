#ifndef MINIONHUB_H
#define MINIONHUB_H

#include <QWidget>
#include "minion.h"
class MinionHub : public QWidget
{
    Q_OBJECT
public:
    explicit MinionHub(QWidget *parent = 0);
    Minion getMinion();
    void addMinion(Minion minion);
};

#endif // MINIONHUB_H
