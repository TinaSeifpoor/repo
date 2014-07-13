#include "movingline.h"
#include <QPainter>
#include "qmath.h"
#include <QGraphicsScene>
class MovingLinePrivate: public QGraphicsItem {
public:
    QRectF _boundingRect;

    MovingLine* p;
    QPointF center;
    QPointF speed;
    int counter;
    int frameLimit;
    QColor color;
    double radius;
    uint expireTime;
    friend class MovingLine;
    MovingLinePrivate(QGraphicsItem *parent, QGraphicsScene *scene,MovingLine* ml):p(ml),
        QGraphicsItem(parent,scene),
        counter(0),
        frameLimit(200)
    {
        color.setRed(qrand()%255);
        color.setGreen(qrand()%255);
        color.setBlue(qrand()%255);
        center= QPointF(qrand()%300,qrand()%300);
    }


    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
        Q_UNUSED(option);
        Q_UNUSED(widget);

//        QPainterPath tailPath;
//        tailPath.addPolygon(QPolygonF(points));
//        QPen tailPen = painter->pen();
//        tailPen.setStyle(Qt::SolidLine);
//        QColor tailColor = color;
//        tailColor.setAlpha(100);
//        tailPen.setColor(tailColor);
//        painter->setPen(tailPen);
//        painter->drawPath(tailPath);

        QPainterPath laserPath;
        laserPath.addEllipse(center,radius,radius);
        QPen laserPen = painter->pen();
        laserPen.setStyle(Qt::SolidLine);
        QColor laserColor = color;
        laserColor.setAlpha(this->counter);
        laserPen.setColor(laserColor);
        QBrush brush = painter->brush();
        brush.setColor(laserColor);
        brush.setStyle(Qt::SolidPattern);
        painter->setBrush(brush);
        painter->setPen(laserPen);
        painter->drawPath(laserPath);

    }




    QRectF boundingRect() const
    {
        QPainterPath laserPath;
        laserPath.addEllipse(center,radius,radius);
        return laserPath.boundingRect();
    }

    double rand(){
        return (double)(qrand()%300)/300;
    }

};

MovingLine::MovingLine(QGraphicsItem *parent, QGraphicsScene *scene, uint expireTime, double radius):
    d(new MovingLinePrivate(parent,scene,this))
{
    d->speed = QPointF((((double)(qrand()%10000)/5000)-1),(((double)(qrand()%10000)/5000)-1));
    d->radius = radius;
    d->expireTime=expireTime;
}

MovingLine::~MovingLine()
{
    delete d;
}

void MovingLine::frame()
{
    QPointF currentPoint = d->center;
    currentPoint+=d->speed;
    if ((currentPoint.x()+d->radius)>d->scene()->sceneRect().right()) {
        currentPoint.setX(d->scene()->sceneRect().right()-d->radius);
        d->speed.setX(-d->speed.x());
    } else  if (currentPoint.x()<d->radius) {
        currentPoint.setX(d->radius);
        d->speed.setX(-d->speed.x());
    }
    if ((currentPoint.y()+d->radius)>d->scene()->sceneRect().bottom()) {
        currentPoint.setY(d->scene()->sceneRect().bottom()-d->radius);
        d->speed.setY(-d->speed.y());
    } else if (currentPoint.y()<d->radius) {
        currentPoint.setY(d->radius);
        d->speed.setY(-d->speed.y());
    }

    double totalSpeed = qSqrt(d->speed.x()*d->speed.x()+d->speed.y()*d->speed.y());

    double newTotalSpeed = totalSpeed+d->rand()/20;

    d->speed.setX(newTotalSpeed/totalSpeed*d->speed.x());
    d->speed.setY(newTotalSpeed/totalSpeed*d->speed.y());

    if (d->counter%d->expireTime==d->expireTime-1) {
        emit miss();
        return;
    }

    d->center = currentPoint;
//    d->points.push_back(currentPoint);
//    d->points.remove(0);
    d->prepareGeometryChange();
    ++d->counter;
}

void MovingLine::randomize()
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

void MovingLine::onMiss()
{
    emit miss();
}

void MovingLine::onHit()
{
    emit hit();
}

void MovingLine::mouseClick(QPointF pos)
{
    QPainterPath laserPath;
    laserPath.addEllipse(d->center,d->radius,d->radius);
    if (laserPath.boundingRect().contains(pos)) {
        emit hit();
    }
}


