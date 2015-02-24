#ifndef CLICKABLECIRCLE_H
#define CLICKABLECIRCLE_H

#include <QGraphicsItem>
class MovingLine;
class ClickableCircle : public QGraphicsItem
{
public:
    ClickableCircle(MovingLine *line=0, QGraphicsItem *parent=0, QGraphicsScene *scene=0);
    void setCenter(const QPointF center);


private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    QPointF center;
    double radius;
    MovingLine* line;
};

#endif // CLICKABLECIRCLE_H
