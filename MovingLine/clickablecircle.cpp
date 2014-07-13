#include "clickablecircle.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include "movingline.h"
ClickableCircle::ClickableCircle(MovingLine *line, QGraphicsItem *parent, QGraphicsScene *scene):
    QGraphicsItem(parent,scene),
    center(QPointF(0,0)),
    radius(20),
    line(line)
{
    this->grabMouse();
    this->hide();
}

void ClickableCircle::setCenter(const QPointF center)
{
    if (this->isVisible()) {
        if (line) {
            line->onMiss();
        }
    }
    this->center=center;
    this->show();
    prepareGeometryChange();
}

void ClickableCircle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->boundingRect().contains(event->pos())) {
        qDebug("clicked");
        this->hide();
        if (line) {
            line->onHit();
        }
    }
}
void ClickableCircle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPainterPath paintPath;
    paintPath.addEllipse(this->center,this->radius,this->radius);
    QPen pen = painter->pen();
    pen.setColor(QColor(30,40,200,200));
    QBrush brush;
    brush.setColor(QColor(30,40,200,100));
    brush.setStyle(Qt::SolidPattern);
    painter->setBrush(brush);
    painter->setPen(pen);
    painter->drawPath(paintPath);
}

QRectF ClickableCircle::boundingRect() const
{
    QPainterPath paintPath;
    paintPath.addEllipse(this->center,this->radius,this->radius);
    return paintPath.boundingRect();

}
