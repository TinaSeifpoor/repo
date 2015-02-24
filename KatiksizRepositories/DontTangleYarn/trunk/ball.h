#ifndef MOVINGLINE_H
#define MOVINGLINE_H

#include <QGraphicsItem>

class BallPrivate;
class Ball : public QObject
{
    Q_OBJECT
public:
    Ball(QGraphicsScene *scene=0, double radius=1);
    ~Ball();
    void setIndex(qint64 idx=-1);

signals:
    void miss(double,qint16);
    void hit(double,qint16);
    void newBall(Ball*);

public slots:
    void frame();
    void randomize();
    void touch(QRegion reg);

private:
    friend class BallPrivate;
    BallPrivate* d;
};

#endif // MOVINGLINE_H
