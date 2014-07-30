#include "ball.h"
#include <QPainter>
#include "qmath.h"
#include <QGraphicsScene>

static QVector<QRgb> colorTable;
class BallPrivate {
public:
    QGraphicsPixmapItem* ellipse;
    QVector<QGraphicsLineItem*> tailOuter;
    QVector<QGraphicsLineItem*> tailInner;
    QVector<QLineF> tailLines;
    QPen tailOuterPen;
    QPen tailInnerPen;
    Ball* p;
    QPointF center;
    QPointF speed;
    QColor color;
    double radius;
    double health;
    double startHealth;
    qint64 idx;
    QPixmap pim;
    friend class Ball;
    BallPrivate(Ball* ml):p(ml)
    {
        color.setRed(qrand()%255);
        color.setGreen(qrand()%255);
        color.setBlue(qrand()%255);
        tailOuterPen.setColor(color);
        tailOuterPen.setWidth(5);
        tailInnerPen.setColor(QColor(255,255,255,255));
        tailInnerPen.setWidth(3);
    }

    ~BallPrivate() {
        ellipse->scene()->removeItem(ellipse);
        delete ellipse;
        foreach (QGraphicsLineItem* item, tailOuter) {
            item->scene()->removeItem(item);
            delete item;
        }
        foreach (QGraphicsLineItem* item, tailInner) {
            item->scene()->removeItem(item);
            delete item;
        }
        tailLines.clear();
    }

    double rand() const{
        return (double)(qrand()%300)/300; // 0.5 mean uniform random variable between 0 and 1
    }

    double r() const {
        return ((double)(qrand()%10000)/1000); // zero mean uniform random variable between -2 and 2
    }

    double heathFromRadius() {
        health = radius*radius/4;
        return health;
    }

    double radiusFromHealth() {
        radius = qSqrt(health*4);
        ellipse->setPixmap(pim.scaled(radius*2,radius*2,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        ellipse->setPos(center.x()-radius, center.y()-radius);
        return radius;
    }

    double dist(QPointF p1, QPointF p2) {
        double xDiff =p1.x() - p2.x();
        double yDiff =p1.y() - p2.y();
        return xDiff*xDiff + yDiff*yDiff;
    }

    void touch(QPointF hitPos) {
        QPointF endSpeed = center-hitPos;
        double den = qSqrt((center-hitPos).x()*(center-hitPos).x() + (center-hitPos).y()*(center-hitPos).y());
        endSpeed /= den;
        endSpeed*=4;
        this->speed = endSpeed;
//        this->speed=(center-hitPos)/radius*3;
    }

    void resetPosition() {
        center.setX(qrand()%(int)(ellipse->scene()->sceneRect().width()-radius*4)+radius*2);
        center.setY(qrand()%(int)(ellipse->scene()->sceneRect().height()-radius*4)+radius*2);
        ellipse->setPos(center.x()-radius, center.y()-radius);
    }

    bool checkLineIntersection(QLineF line1, QLineF line2, QPointF *point) const {
        qint64 x1 = line1.x1();
        qint64 x2 = line1.x2();
        qint64 x3 = line2.x1();
        qint64 x4 = line2.x2();
        qint64 y1 = line1.y1();
        qint64 y2 = line1.y2();
        qint64 y3 = line2.y1();
        qint64 y4 = line2.y2();

        double PxNom =  (x1*y2 - y1*x2)*(x3-x4) - (x1-x2)*(x3*y4 - y3*x4);
        qint64 den =  (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);
        if (den<2 && den>-2)
            return false;
        double Px = PxNom/den;
        double PyNom =  (x1*y2 - y1*x2)*(y3-y4) -
                (y1-y2)*(x3*y4 - y3*x4);
        double Py = PyNom/den;
        qint64 xLower1 = qMin(x1,x2);
        qint64 xHigher2 = qMax(x1,x2);
        qint64 yLower1 = qMin(y1,y2);
        qint64 yHigher2 = qMax(y1,y2);
        qint64 xLower3 = qMin(x3,x4);
        qint64 xHigher4 = qMax(x3,x4);
        qint64 yLower3 = qMin(y3,y4);
        qint64 yHigher4 = qMax(y3,y4);
        if (Py<yLower3 || Py>yHigher4 || Py<yLower1 || Py>yHigher2)
            return false;
        if (Px<xLower1 || Px>xHigher2 || Px<xLower3 || Px>xHigher4)
            return false;
        if (point) {
            point->setX(Px);
            point->setY(Py);
        }
        return true;
    }
};

Ball::Ball(QGraphicsScene *scene, double radius):
    d(new BallPrivate(this))
{
    d->radius = radius;
    d->heathFromRadius();
    d->startHealth = d->health;

    QImage im(":/images/ball");
    d->color.setAlpha(200);
    im.setColor(0,d->color.rgb());
    d->pim=QPixmap::fromImage(im);
    d->ellipse = scene->addPixmap(d->pim.scaled(d->radius*2, d->radius*2,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    d->ellipse->setZValue(5);
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
    d->ellipse->moveBy(d->speed.x(), d->speed.y());
    QPointF oldCenter = d->center;
    d->center += d->speed;
    QRectF sceneRect = d->ellipse->scene()->sceneRect();
    QRectF ellipseRect(QPointF(d->center.x()-d->radius, d->center.y()-d->radius),
                       QPointF(d->center.x()+d->radius, d->center.y()+d->radius));
    if (    ellipseRect.left() < sceneRect.left() ||
            ellipseRect.right() > sceneRect.right() ||
            ellipseRect.top() < sceneRect.top() ||
            ellipseRect.bottom() > sceneRect.bottom()) {
        emit miss(d->health, d->idx);
    }
    QPointF distance = oldCenter-d->center;
    double distanceTraveled = qSqrt(distance.x()*distance.x()+distance.y()*distance.y());
    if (distanceTraveled) {
        QLineF line(oldCenter,d->center);
        for (int i=0; i<d->tailLines.count()-1; ++i) {
            if (d->checkLineIntersection(line, d->tailLines.at(i),0)){
                emit miss(d->health, d->idx);
                return;
            }
        }
        d->tailLines.append(line);
        d->tailOuter << d->ellipse->scene()->addLine(line,d->tailOuterPen);
        d->tailInner << d->ellipse->scene()->addLine(line,d->tailInnerPen);
        d->health-=distanceTraveled;
        if (d->health<=0)
            emit hit(d->startHealth,d->idx);
        d->radiusFromHealth();
    }
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

void Ball::touch(QRegion reg)
{
    QRect rect = QRect(0,0,d->radius*2, d->radius*2);
    rect.moveCenter(d->center.toPoint());
    QRegion a = QRegion(rect, QRegion::Ellipse);
    if (reg.intersects(a)) {
        d->touch(reg.boundingRect().center());
    }
}
