#include "movingline.h"
#include <QPainter>
#include "qmath.h"
#include <QGraphicsScene>
class BallPrivate {
public:
    QGraphicsEllipseItem* ellipse;
    Ball* p;
    QPointF center;
    QPointF speed;
    int counter;
    QColor color;
    double radius;
    uint expireTime;
    double health;
    qint64 idx;
    friend class Ball;
    BallPrivate(Ball* ml):p(ml),
        counter(0)
    {
        color.setRed(qrand()%255);
        color.setGreen(qrand()%255);
        color.setBlue(qrand()%255);
        center= QPointF(qrand()%250+25,qrand()%250+25);
    }

    ~BallPrivate() {
        ellipse->scene()->removeItem(ellipse);
        delete ellipse;
    }

    double rand() const{
        return (double)(qrand()%300)/300; // 0.5 mean uniform random variable between 0 and 1
    }

    double r() const {
        return ((double)(qrand()%10000)/5000)-1; // zero mean uniform random variable between -1 and 1
    }

    void setDraw() {
        QPen laserPen = ellipse->pen();
        QColor laserColor = laserPen.color();
        laserColor.setAlpha(this->counter);
        laserPen.setColor(laserColor);
        ellipse->setPen(laserPen);

        QBrush brush = ellipse->brush();
        brush.setColor(laserColor);
        if (health>3)
            brush.setStyle(Qt::SolidPattern);
        else if (health > 1)
            brush.setStyle(Qt::CrossPattern);
        else
            brush.setStyle(Qt::Dense3Pattern);
        ellipse->setBrush(brush);
    }



};

Ball::Ball(QGraphicsScene *scene,
                       uint expireTime, double radius, double health, qint64 idx):
    d(new BallPrivate(this))
{
    d->health=health;
    d->idx=idx;
    d->radius = radius;
    d->speed = QPointF(d->r()/2,d->r()/2);
    d->expireTime=expireTime;
    d->ellipse = scene->addEllipse(d->center.x(), d->center.y(), radius,radius);
    //
    QPen laserPen = d->ellipse->pen();
    laserPen.setStyle(Qt::SolidLine);
    QColor laserColor = d->color;
    laserColor.setAlpha(d->counter);
    laserPen.setColor(laserColor);
    d->ellipse->setPen(laserPen);
    //

    d->setDraw();
}

Ball::~Ball()
{
    delete d;
}

void Ball::frame()
{
    if (d->counter%d->expireTime==d->expireTime-1) {
        emit miss(d->idx);
        return;
    }
    d->ellipse->moveBy(d->speed.x(), d->speed.y());
    QRectF sceneRect = d->ellipse->mapRectFromScene(d->ellipse->scene()->sceneRect());
    QRectF ellipseRect = d->ellipse->rect();
        if (    ellipseRect.left() < sceneRect.left() ||
                ellipseRect.right() > sceneRect.right()) {
            d->speed.setX(-d->speed.x());
            d->ellipse->moveBy(2*d->speed.x(),0);
        }
        if (    ellipseRect.top() < sceneRect.top() ||
                ellipseRect.bottom() > sceneRect.bottom()) {
            d->speed.setY(-d->speed.y());
            d->ellipse->moveBy(0,2*d->speed.y());
        }

    double totalSpeed = qSqrt(d->speed.x()*d->speed.x()+d->speed.y()*d->speed.y());

    double newTotalSpeed = totalSpeed+d->rand()/100;

    d->speed.setX(newTotalSpeed/totalSpeed*d->speed.x());
    d->speed.setY(newTotalSpeed/totalSpeed*d->speed.y());

    ++d->counter;
    d->setDraw();
}

void Ball::randomize()
{
    double totalSpeed = qSqrt(d->speed.x()*d->speed.x()+d->speed.y()*d->speed.y());
    double deg = qrand()%720;
    double degNorm = deg/720*3.1416;
    d->speed.setX(totalSpeed*sin(degNorm));
    if (qrand()%2)
        d->speed.setX(-d->speed.x());
    d->speed.setY(totalSpeed*cos(degNorm));
    if (qrand()%2)
        d->speed.setY(-d->speed.y());
}

void Ball::mouseClick(QPointF pos)
{
    QPointF mappedPos = d->ellipse->mapFromScene(pos);
    QRectF rect = d->ellipse->boundingRect();
    if (d->ellipse->contains(mappedPos)) {
        --d->health;
        d->setDraw();
        randomize();
        if (d->health<1)
            emit hit(d->idx);
    }
}



