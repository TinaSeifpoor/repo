#ifndef MOVINGLINE_H
#define MOVINGLINE_H

#include <QGraphicsItem>

class BallPrivate;
class Ball : public QObject
{
    Q_OBJECT
public:
    Ball(QGraphicsScene *scene=0,
               uint expireTime=150, double radius=20, double health=1,
               qint64 idx=-1);
    ~Ball();

signals:
    void miss(qint16);
    void hit(qint16);

public slots:
    void frame();
    void randomize();
    void mouseClick(QPointF pos);

private:
    friend class BallPrivate;
    BallPrivate* d;
};

#endif // MOVINGLINE_H
