#ifndef ATTACK_H
#define ATTACK_H

#include <QObject>
#include <QLine>
#include <QRegion>
class QGraphicsScene;
class Attack : public QObject {
    Q_OBJECT
public:
    Attack(double maulRadius, double swipeLength1, double swipeLength2, QObject *parent=0);
    void press(QPointF pos, Qt::MouseButtons buttons);
    void swipe(qreal angle, QPointF pos);
    void release(QPointF pos);
signals:
    void attackMaul(QRegion reg);
    void attackSwipe(QLineF reg);
private:
    enum AttackType {
        Regular,
        Swipe,
        Maul
    } currentAttackType;
    bool isMoving;
    QPointF startPoint;
    double swipeLength1;
    double swipeLength2;
    double maulRadius;
};

#endif // ATTACK_H
