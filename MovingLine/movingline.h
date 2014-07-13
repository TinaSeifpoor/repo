#ifndef MOVINGLINE_H
#define MOVINGLINE_H

#include <QGraphicsItem>

class MovingLinePrivate;
class MovingLine : public QObject
{
    Q_OBJECT
public:
    MovingLine(QGraphicsItem *parent = 0, QGraphicsScene *scene=0, uint expireTime=150, double radius=20);
    ~MovingLine();

signals:
    void miss();
    void hit();

public slots:
    void frame();
    void randomize();
    void onMiss();
    void onHit();
    void mouseClick(QPointF pos);

private:
    friend class MovingLinePrivate;
    MovingLinePrivate* d;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
};

#endif // MOVINGLINE_H
