#ifndef MOVINGLINE_H
#define MOVINGLINE_H

#include <QGraphicsItem>

class MovingLinePrivate;
class MovingLine : public QObject
{
    Q_OBJECT
public:
    MovingLine(QGraphicsItem *parent = 0, QGraphicsScene *scene=0);
    ~MovingLine();

signals:
    void miss();
    void hit();

public slots:
    void frame();
    void randomize();
    void onMiss();
    void onHit();

private:
    friend class MovingLinePrivate;
    MovingLinePrivate* d;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
};

#endif // MOVINGLINE_H
