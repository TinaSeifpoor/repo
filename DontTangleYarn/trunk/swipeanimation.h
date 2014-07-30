#ifndef SWIPEANIMATION_H
#define SWIPEANIMATION_H

class QGraphicsScene;
class QGraphicsLineItem;
#include <QLineF>
#include <QObject>
class SwipeAnimation : public QObject
{
    Q_OBJECT
public:
    SwipeAnimation(QLineF line, QGraphicsScene* scene=0);
public slots:
    void deleteLine();
private:
    QGraphicsLineItem* itemInner;
    QGraphicsLineItem* itemOuter;
};

#endif // SWIPEANIMATION_H
