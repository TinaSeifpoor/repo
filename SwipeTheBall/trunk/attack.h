#ifndef ATTACK_H
#define ATTACK_H

#include <QObject>
#include <QLine>
#include <QRegion>
class Attack : public QObject {
    Q_OBJECT
public:
    Attack::Attack(QObject *parent=0) :
        QObject(parent)
    {
    }


    void press(QPointF pos, Qt::MouseButtons buttons) {
        if (buttons&Qt::LeftButton) {
            currentAttackType = Regular;
            QRegion reg = QRegion(QRect(pos.toPoint()-QPoint(20,20),pos.toPoint()+QPoint(20,20)),QRegion::Ellipse);
            emit attackMaul(reg);
        } else if (buttons&Qt::RightButton){
            if (currentAttackType==Swipe) {
                QLineF reg = QLineF(this->startPoint, pos);
                currentAttackType = Regular;
                emit attackSwipe(reg);
            } else {
                currentAttackType = Swipe;
                startPoint = pos;
                return;
            }
        }
    }
signals:

    void attackMaul(QRegion reg);
    void attackSwipe(QLineF reg);
private:
    //    QRegion calculateSwipe(QPointF endPoint) {
    //        double slope = atan2(endPoint.y()-startPoint.y(), endPoint.x()-startPoint.x());
    //        QPointF center((startPoint.x()+endPoint.x())/2, (startPoint.y()+endPoint.y())/2);
    //        QPointF topLeft(center-QPointF(slope*10,10/slope));
    //        QPointF bottomRight(center+QPointF(slope*10,10/slope));
    //        QRectF swipeRect(topLeft, bottomRight);
    //        emit attackSwipe(QRegion(swipeRect));
    //    }

    enum AttackType {
        Regular,
        Swipe,
        Maul
    } currentAttackType;
    bool isMoving;
    QPointF startPoint;
};

#endif // ATTACK_H
