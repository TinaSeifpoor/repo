#include "attack.h"
Attack::Attack(double maulRadius, double swipeLength1, double swipeLength2, QObject *parent) :
    QObject(parent),
    maulRadius(maulRadius),
    swipeLength1(swipeLength1),
    swipeLength2(swipeLength2)
{
}

void Attack::press(QPointF pos, Qt::MouseButtons buttons) {
    this->startPoint = pos;
}

void Attack::release(QPointF pos)
{
    QLineF line(this->startPoint,pos);
    if (line.length()<swipeLength1) {
        QRegion reg = QRegion(QRect(pos.toPoint()-QPoint(maulRadius,maulRadius),pos.toPoint()+QPoint(maulRadius,maulRadius)),QRegion::Ellipse);
        emit attackMaul(reg);
    } else {
        QLineF lineCenter(this->startPoint, pos);
        lineCenter.setLength(swipeLength1);
        QLineF lineCenterToUp = lineCenter.normalVector();
        lineCenterToUp.setLength(swipeLength2);
        QPointF point1Up = lineCenterToUp.p1();
        QPointF point2Up = lineCenterToUp.p2();
        lineCenterToUp.setP1(point2Up);
        lineCenterToUp.setP2(point1Up);
        QLineF lineUp = lineCenterToUp.normalVector();
        lineUp.setLength(swipeLength1);
        QLineF lineCenterToDown = lineCenter.normalVector();
        lineCenterToDown.setLength(-swipeLength2);
        QPointF point1Down = lineCenterToDown.p1();
        QPointF point2Down = lineCenterToDown.p2();
        lineCenterToDown.setP1(point2Down);
        lineCenterToDown.setP2(point1Down);
        QLineF lineDown = lineCenterToDown.normalVector();
        lineDown.setLength(-swipeLength1);
        currentAttackType = Regular;
        emit attackSwipe(lineCenter);
        emit attackSwipe(lineUp);
        emit attackSwipe(lineDown);
    }
}

