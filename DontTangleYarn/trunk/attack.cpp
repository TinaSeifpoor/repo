#include "attack.h"
Attack::Attack(double maulRadius, QObject *parent) :
    QObject(parent),
    maulRadius(maulRadius)
{
}

void Attack::release(QPointF pos)
{
    QRegion reg = QRegion(QRect(pos.toPoint()-QPoint(maulRadius,maulRadius),pos.toPoint()+QPoint(maulRadius,maulRadius)),QRegion::Ellipse);
    emit attackMaul(reg);
}

