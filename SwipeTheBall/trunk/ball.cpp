#include "ball.h"
#include <QPainter>
#include "qmath.h"
#include <QGraphicsScene>
static QVector<QRgb> colorTable;

class BallPrivate {
public:
    QGraphicsPixmapItem* ellipse;
    Ball* p;
    QPointF center;
    QPointF speed;
    int counter;
    QColor color;
    double radius;
    uint expireTime;
    double health;
    qint64 idx;
    int maulDamage;
    int swipeDamage;
    friend class Ball;
    BallPrivate(Ball* ml):p(ml),
        counter(0)
    {
        color.setRed(qrand()%255);
        color.setGreen(qrand()%255);
        color.setBlue(qrand()%255);
        center= QPointF(qrand()%550+25,qrand()%550+25);
//        center = QPointF(5,5);
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

    //    void setDraw() {


    //        QImage im(":/images/ball");
    //        im.setColor(0,ellipse->pen().color().rgb());
    //        im.setColor(255,QColor(150,150,150,150).rgb());
    //        QPixmap pim=QPixmap::fromImage(im);

    //            ellipse->setBrush(pim.scaled(radius*2, radius*2,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));


    ////        QPen laserPen = ellipse->pen();
    ////        QColor laserColor = laserPen.color();
    ////        laserColor.setAlpha(180);
    ////        laserPen.setColor(laserColor);
    ////        ellipse->setPen(laserPen);

    ////        QBrush brush = ellipse->brush();
    ////        brush.setColor(laserColor);
    ////            brush.setStyle((Qt::BrushStyle)((int)health));
    ////        ellipse->setBrush(brush);
    //    }

    double dist(QPointF p1, QPointF p2) {
        double xDiff =p1.x() - p2.x();
        double yDiff =p1.y() - p2.y();
        return xDiff*xDiff + yDiff*yDiff;
    }



};

Ball::Ball(QGraphicsScene *scene,
           uint expireTime, double radius, double health, int maulDamage, int swipeDamage,qint64 idx):
    d(new BallPrivate(this))
{
    d->health=health;
    d->idx=idx;
    d->radius = radius;
    d->swipeDamage = swipeDamage;
    d->maulDamage = maulDamage;
    d->speed = QPointF(d->r()/2,d->r()/2);
    d->expireTime=expireTime;

    QImage im(":/images/ball");
    d->color.setAlpha(200);
    im.setColor(0,d->color.rgb());
    QPixmap pim=QPixmap::fromImage(im);

    d->ellipse = scene->addPixmap(pim.scaled(radius*2, radius*2,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    d->ellipse->moveBy(d->center.x()-radius, d->center.y()-radius);

//    d->setDraw();
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
    d->center += d->speed;
    QRectF sceneRect = QRectF(0,0,600,600);
    QRectF ellipseRect(QPointF(d->center.x()-d->radius, d->center.y()-d->radius),
                       QPointF(d->center.x()+d->radius, d->center.y()+d->radius));
    if (    ellipseRect.left() < sceneRect.left() ||
            ellipseRect.right() > sceneRect.right()) {
        d->speed.setX(-d->speed.x());
        d->ellipse->moveBy(2*d->speed.x(),0);
        d->center += QPointF(2*d->speed.x(),0);
    }
    if (    ellipseRect.top() < sceneRect.top() ||
            ellipseRect.bottom() > sceneRect.bottom()) {
        d->speed.setY(-d->speed.y());
        d->ellipse->moveBy(0,2*d->speed.y());
        d->center += QPointF(0,2*d->speed.y());
    }

    double totalSpeed = qSqrt(d->speed.x()*d->speed.x()+d->speed.y()*d->speed.y());

    double newTotalSpeed = totalSpeed+d->rand()/100;

    d->speed.setX(newTotalSpeed/totalSpeed*d->speed.x());
    d->speed.setY(newTotalSpeed/totalSpeed*d->speed.y());

    ++d->counter;
//    d->setDraw();
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

void Ball::attackMaul(QRegion reg)
{
    QRect rect = QRect(0,0,d->radius*2, d->radius*2);
    rect.moveCenter(d->center.toPoint());
    QRegion a = QRegion(rect, QRegion::Ellipse);
    if (reg.intersects(a)) {
        d->health-=d->maulDamage;
//        d->setDraw();
        randomize();
        if (d->health<1)
            emit hit(d->idx);
    }
}

void Ball::attackSwipe(QLineF reg)
{
    QPointF w = reg.p1(),
            v = reg.p2(),
            p = d->center;
    double t = ((p.x()-v.x()) * (w.x()-v.x())+
                ((p.y()-v.y()) * (w.y()-v.y())));
    double dist = d->dist(v,w);
    t/=dist;
    if (t<0) {
        dist = d->dist(v,p);
    } else if (t>1) {
        dist = d->dist(w,p);
    } else {
        QPointF z(v.x()+t*(w.x()-v.x()), v.y()+t*(w.y()-v.y()));
        dist = d->dist(p,z);
    }
    if (dist<(d->radius*d->radius)) {
        d->health-=d->swipeDamage;
//        d->setDraw();
        randomize();
        if (d->health<1)
            emit hit(d->idx);
    }
}