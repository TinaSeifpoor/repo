#ifndef MOVINGLINE_H
#define MOVINGLINE_H

#include <QGraphicsItem>

class BallPrivate;
class Ball : public QObject
{
    Q_OBJECT
public:
    Ball(QGraphicsScene *scene=0,
               uint expireTime=150, double health=1, int maulDamage=3, int swipeDamage=1,
               qint64 idx=-1);
    ~Ball();
    void setIndex(qint64 idx=-1);

signals:
    void miss(qint16);
    void hit(qint16);
    void newBall(Ball*);

public slots:
    void frame();
    void randomize();
    void attackMaul(QRegion reg);
    void attackSwipe(QLineF reg);

private:
    friend class BallPrivate;
    BallPrivate* d;
};

#endif // MOVINGLINE_H
