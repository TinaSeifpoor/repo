#ifndef ATTACK_H
#define ATTACK_H

#include <QObject>
#include <QLine>
#include <QRegion>
class QGraphicsScene;
class Attack : public QObject {
    Q_OBJECT
public:
    Attack(double maulRadius, QObject *parent=0);
    void release(QPointF pos);
signals:
    void attackMaul(QRegion reg);

private:
    double maulRadius;
};

#endif // ATTACK_H
