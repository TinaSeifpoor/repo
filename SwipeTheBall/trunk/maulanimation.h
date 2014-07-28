#ifndef MAULANIMATION_H
#define MAULANIMATION_H

class QGraphicsScene;
class QGraphicsEllipseItem;
#include <QRegion>
class MaulAnimation : public QObject
{
    Q_OBJECT
public:
    MaulAnimation(QRegion reg, QGraphicsScene* scene=0);
public slots:
    void deleteLine();
private:
    QGraphicsEllipseItem* item;
};

#endif // MAULANIMATION_H
