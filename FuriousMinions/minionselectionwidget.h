#ifndef MINIONSELECTIONWIDGET_H
#define MINIONSELECTIONWIDGET_H

#include <QCheckBox>
class MinionTemplate;
class MinionSelectionWidget : public QCheckBox
{
    Q_OBJECT
    MinionTemplate* __mt;
public:
    explicit MinionSelectionWidget(MinionTemplate* mt, QWidget *parent = 0);

signals:

public slots:

};

#endif // MINIONSELECTIONWIDGET_H
