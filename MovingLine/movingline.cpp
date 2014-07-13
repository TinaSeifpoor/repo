#include "movingline.h"
#include <QPainter>
#include "qmath.h"
#include "clickablecircle.h"
class MovingLinePrivate: public QGraphicsItem {
public:
    QRectF _boundingRect;

    MovingLine* p;
    QVector<QPointF> points;
    QPointF speed;
    int counter;
    int frameLimit;
    ClickableCircle* circle;
    friend class MovingLine;
    MovingLinePrivate(QGraphicsItem *parent, QGraphicsScene *scene,MovingLine* ml):p(ml),
        QGraphicsItem(parent,scene),
        counter(0),
        circle(new ClickableCircle(p,this,scene)),
        frameLimit(200)
    {
        for (int i=0; i<50; ++i) {
            points << QPointF(50,50);
        }
        if (_boundingRect.isEmpty() && !points.isEmpty()) {
            foreach (QPointF point, points) {
                if (point.x() < _boundingRect.left()) {
                    _boundingRect.setLeft(point.x());
                } else if (point.x() > _boundingRect.right()) {
                    _boundingRect.setRight(point.x());
                }
                if (point.y() < _boundingRect.top()) {
                    _boundingRect.setTop(point.y());
                } else if (point.y() > _boundingRect.bottom()) {
                    _boundingRect.setBottom(point.y());
                }
            }
        }
    }


    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
        Q_UNUSED(option);
        Q_UNUSED(widget);

        QPainterPath paintPath;
        paintPath.addPolygon(QPolygonF(points));
        QPen pen = painter->pen();
        pen.setStyle(Qt::SolidLine);
        pen.setColor(QColor(200,60,60,240));
        painter->setPen(pen);
        painter->drawPath(paintPath);
    }




    QRectF boundingRect() const
    {
        return _boundingRect;
    }

    double rand(){
        return (double)(qrand()%300)/300;
    }

};

MovingLine::MovingLine(QGraphicsItem *parent, QGraphicsScene *scene):
    d(new MovingLinePrivate(parent,scene,this))
{
    d->speed = QPointF(1,1);
}

MovingLine::~MovingLine()
{
    delete d;
}

void MovingLine::frame()
{
    QPointF currentPoint = d->points.last();
    currentPoint+=d->speed;
    if (currentPoint.x()>300) {
        currentPoint.setX(600-currentPoint.x());
        d->speed.setX(-d->speed.x());
    } else if (currentPoint.x()<0) {
        currentPoint.setX(-currentPoint.x());
        d->speed.setX(-d->speed.x());
    }
    if (currentPoint.y()>300) {
        currentPoint.setY(600-currentPoint.y());
        d->speed.setY(-d->speed.y());
    } else if (currentPoint.y()<0) {
        currentPoint.setY(-currentPoint.y());
        d->speed.setY(-d->speed.y());
    }

    double totalSpeed = qSqrt(d->speed.x()*d->speed.x()+d->speed.y()*d->speed.y());

    double newTotalSpeed = totalSpeed+d->rand()/20;

    d->speed.setX(newTotalSpeed/totalSpeed*d->speed.x());
    d->speed.setY(newTotalSpeed/totalSpeed*d->speed.y());

    if (d->counter%d->frameLimit==0) {
        d->circle->setCenter(currentPoint);
        randomize();
        if (d->frameLimit>10)
            --d->frameLimit;
    }
    if (currentPoint.x() < d->_boundingRect.left()) {
        d->_boundingRect.setLeft(currentPoint.x());
    } else if (currentPoint.x() > d->_boundingRect.right()) {
        d->_boundingRect.setRight(currentPoint.x());
    }
    if (currentPoint.y() < d->_boundingRect.top()) {
        d->_boundingRect.setTop(currentPoint.y());
    } else if (currentPoint.y() > d->_boundingRect.bottom()) {
        d->_boundingRect.setBottom(currentPoint.y());
    }


    d->points.push_back(currentPoint);
    d->points.remove(0);
    d->prepareGeometryChange();
    ++d->counter;

}

void MovingLine::randomize()
{
    double totalSpeed = qSqrt(d->speed.x()*d->speed.x()+d->speed.y()*d->speed.y());
    int lim = totalSpeed*1000;
    d->speed.setX((double)(qrand()%lim)/1000);
    d->speed.setY(qSqrt(totalSpeed*totalSpeed-d->speed.x()*d->speed.x()));
}

void MovingLine::onMiss()
{
    emit miss();
}

void MovingLine::onHit()
{
    emit hit();
}


