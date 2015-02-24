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
    double startHealth;
    qint64 idx;
    int maulDamage;
    int swipeDamage;
    QPixmap pim;
    friend class Ball;
    BallPrivate(Ball* ml):p(ml),
        counter(0)
    {
        color.setRed(qrand()%255);
        color.setGreen(qrand()%255);
        color.setBlue(qrand()%255);
    }

    ~BallPrivate() {
        ellipse->scene()->removeItem(ellipse);
        delete ellipse;
    }

    double rand() const{
        return (double)(qrand()%300)/300; // 0.5 mean uniform random variable between 0 and 1
    }

    double r() const {
        return ((double)(qrand()%10000)/1000); // zero mean uniform random variable between -2 and 2
    }

    double radiusFromHealth() {
        radius = (4 + health)*8;
        return radius;
    }

    double dist(QPointF p1, QPointF p2) {
        double xDiff =p1.x() - p2.x();
        double yDiff =p1.y() - p2.y();
        return xDiff*xDiff + yDiff*yDiff;
    }

    void attack(int damage) {
        for (int i=0; i<damage; ++i) {
            --health;
        }
        p->randomize();
        if (health<=0)
            emit p->hit(startHealth,idx);
        radiusFromHealth();
        ellipse->setPixmap(pim.scaled(radius*2,radius*2,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        ellipse->setPos(center.x()-radius, center.y()-radius);
    }

    void resetPosition() {
        center.setX(qrand()%(int)(ellipse->scene()->sceneRect().width()-radius*4)+radius*2);
        center.setY(qrand()%(int)(ellipse->scene()->sceneRect().height()-radius*4)+radius*2);
        ellipse->setPos(center.x()-radius, center.y()-radius);
    }


};

Ball::Ball(QGraphicsScene *scene,
           uint expireTime, double health, int maulDamage, int swipeDamage,qint64 idx):
    d(new BallPrivate(this))
{
    d->startHealth = health;
    d->health=health;
    d->idx=idx;
    d->radiusFromHealth();
    d->swipeDamage = swipeDamage;
    d->maulDamage = maulDamage;
    d->speed = QPointF(d->r(),0);
    randomize();
    d->expireTime=expireTime;

    QImage im(":/images/ball");
    d->color.setAlpha(200);
    im.setColor(0,d->color.rgb());
    d->pim=QPixmap::fromImage(im);
    d->ellipse = scene->addPixmap(d->pim.scaled(d->radius*2, d->radius*2,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    d->resetPosition();
}

Ball::~Ball()
{
    delete d;
}

void Ball::setIndex(qint64 idx)
{
    d->idx = idx;
}

void Ball::frame()
{
    if (d->counter%d->expireTime==d->expireTime-1) {
        emit miss(d->health,d->idx);
        return;
    }
    d->ellipse->moveBy(d->speed.x(), d->speed.y());
    d->center += d->speed;
    QRectF sceneRect = d->ellipse->scene()->sceneRect();
    QRectF ellipseRect(QPointF(d->center.x()-d->radius, d->center.y()-d->radius),
                       QPointF(d->center.x()+d->radius, d->center.y()+d->radius));
    if (    ellipseRect.left() < sceneRect.left() ||
            ellipseRect.right() > sceneRect.right()) {
        d->resetPosition();
        randomize();
    }
    if (    ellipseRect.top() < sceneRect.top() ||
            ellipseRect.bottom() > sceneRect.bottom()) {
        d->resetPosition();
        randomize();
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
        d->attack(d->maulDamage);
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
        d->attack(d->swipeDamage);
    }
}
