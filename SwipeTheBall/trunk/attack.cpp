#include "attack.h"
Attack::Attack(double maulRadius, double swipeLength1, double swipeLength2, QObject *parent) :
    QObject(parent),
    maulRadius(maulRadius),
    swipeLength1(swipeLength1),
    swipeLength2(swipeLength2)
{
}

void debugLine(QString lineName, QLineF line) {
//    qDebug(QString("P1: (%1,%2), P2: (%3,%4), Line: %5").
//           arg(line.p1().x()).arg(line.p1().y()).
//           arg(line.p2().x()).arg(line.p2().y()).
//           arg(lineName).toLatin1());
}

void Attack::press(QPointF pos, Qt::MouseButtons buttons) {
    this->startPoint = pos;
//        if (buttons&Qt::LeftButton) {
//            currentAttackType = Regular;
//            QRegion reg = QRegion(QRect(pos.toPoint()-QPoint(maulRadius,maulRadius),pos.toPoint()+QPoint(maulRadius,maulRadius)),QRegion::Ellipse);
//            emit attackMaul(reg);
//        } else if (buttons&Qt::RightButton){
//            if (currentAttackType==Swipe) {
//                QLineF lineCenter(this->startPoint, pos);
//                lineCenter.setLength(swipeLength1);
//                debugLine("lineCenter", lineCenter);
//                QLineF lineCenterToUp = lineCenter.normalVector();
//                lineCenterToUp.setLength(swipeLength2);
//                QPointF point1Up = lineCenterToUp.p1();
//                QPointF point2Up = lineCenterToUp.p2();
//                lineCenterToUp.setP1(point2Up);
//                lineCenterToUp.setP2(point1Up);
//                debugLine("lineCenterToUp", lineCenterToUp);
//                QLineF lineUp = lineCenterToUp.normalVector();
//                lineUp.setLength(swipeLength1);
//                debugLine("lineUp", lineUp);
//                QLineF lineCenterToDown = lineCenter.normalVector();
//                lineCenterToDown.setLength(-swipeLength2);
//                QPointF point1Down = lineCenterToDown.p1();
//                QPointF point2Down = lineCenterToDown.p2();
//                lineCenterToDown.setP1(point2Down);
//                lineCenterToDown.setP2(point1Down);
//                debugLine("lineCenterToDown", lineCenterToDown);
//                QLineF lineDown = lineCenterToDown.normalVector();
//                lineDown.setLength(-swipeLength1);
//                debugLine("lineDown", lineDown);
//                currentAttackType = Regular;
//                emit attackSwipe(lineCenter);
//                emit attackSwipe(lineUp);
//                emit attackSwipe(lineDown);
//            } else {
//                currentAttackType = Swipe;
//                startPoint = pos;
//                return;
//            }
//        }
}

//void Attack::swipe(qreal angle, QPointF pos)
//{
//    QLineF lineCenter(pos, pos);
//    lineCenter.setLength(swipeLength1);
//    lineCenter.setAngle(angle);
//    QPointF P2 = (lineCenter.p1()+lineCenter.p2())/2;
//    lineCenter.setAngle(-angle);
//    QPointF P1 = (lineCenter.p1()+lineCenter.p2())/2;
//    lineCenter.setP1(P1);
//    lineCenter.setP1(P2);

//    lineCenter.setLength(swipeLength1);
//    debugLine("lineCenter", lineCenter);
//    QLineF lineCenterToUp = lineCenter.normalVector();
//    lineCenterToUp.setLength(swipeLength2);
//    QPointF point1Up = lineCenterToUp.p1();
//    QPointF point2Up = lineCenterToUp.p2();
//    lineCenterToUp.setP1(point2Up);
//    lineCenterToUp.setP2(point1Up);
//    debugLine("lineCenterToUp", lineCenterToUp);
//    QLineF lineUp = lineCenterToUp.normalVector();
//    lineUp.setLength(swipeLength1);
//    debugLine("lineUp", lineUp);
//    QLineF lineCenterToDown = lineCenter.normalVector();
//    lineCenterToDown.setLength(-swipeLength2);
//    QPointF point1Down = lineCenterToDown.p1();
//    QPointF point2Down = lineCenterToDown.p2();
//    lineCenterToDown.setP1(point2Down);
//    lineCenterToDown.setP2(point1Down);
//    debugLine("lineCenterToDown", lineCenterToDown);
//    QLineF lineDown = lineCenterToDown.normalVector();
//    lineDown.setLength(-swipeLength1);
//    debugLine("lineDown", lineDown);
//    currentAttackType = Regular;
//    emit attackSwipe(lineCenter);
//    emit attackSwipe(lineUp);
//    emit attackSwipe(lineDown);
//}

void Attack::release(QPointF pos, Qt::MouseButtons buttons)
{
    QLineF line(this->startPoint,pos);
    if (line.length()<15) {
        QRegion reg = QRegion(QRect(pos.toPoint()-QPoint(maulRadius,maulRadius),pos.toPoint()+QPoint(maulRadius,maulRadius)),QRegion::Ellipse);
        emit attackMaul(reg);
    } else {
        QLineF lineCenter(this->startPoint, pos);
        lineCenter.setLength(swipeLength1);
        debugLine("lineCenter", lineCenter);
        QLineF lineCenterToUp = lineCenter.normalVector();
        lineCenterToUp.setLength(swipeLength2);
        QPointF point1Up = lineCenterToUp.p1();
        QPointF point2Up = lineCenterToUp.p2();
        lineCenterToUp.setP1(point2Up);
        lineCenterToUp.setP2(point1Up);
        debugLine("lineCenterToUp", lineCenterToUp);
        QLineF lineUp = lineCenterToUp.normalVector();
        lineUp.setLength(swipeLength1);
        debugLine("lineUp", lineUp);
        QLineF lineCenterToDown = lineCenter.normalVector();
        lineCenterToDown.setLength(-swipeLength2);
        QPointF point1Down = lineCenterToDown.p1();
        QPointF point2Down = lineCenterToDown.p2();
        lineCenterToDown.setP1(point2Down);
        lineCenterToDown.setP2(point1Down);
        debugLine("lineCenterToDown", lineCenterToDown);
        QLineF lineDown = lineCenterToDown.normalVector();
        lineDown.setLength(-swipeLength1);
        debugLine("lineDown", lineDown);
        currentAttackType = Regular;
        emit attackSwipe(lineCenter);
        emit attackSwipe(lineUp);
        emit attackSwipe(lineDown);
    }
}

