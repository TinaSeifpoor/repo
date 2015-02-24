#include "swipeanimation.h"
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QColor>
SwipeAnimation::SwipeAnimation(QLineF line, QGraphicsScene *scene){
    QPen swipePenOuter;
    swipePenOuter.setStyle(Qt::SolidLine);
    swipePenOuter.setWidth(4);
    QColor swipeColorOuter = QColor(40,80,80,150);
    swipePenOuter.setColor(swipeColorOuter);
    itemOuter = scene->addLine(line, swipePenOuter);    QPen swipePenInner;
    swipePenInner.setStyle(Qt::SolidLine);
    swipePenInner.setWidth(2);
    QColor swipeColorInner = QColor(250,250,250,150);
    swipePenInner.setColor(swipeColorInner);
    itemInner = scene->addLine(line, swipePenInner);
}

void SwipeAnimation::deleteLine()
{
    itemInner->scene()->removeItem(itemInner);
    delete itemInner;
    itemOuter->scene()->removeItem(itemOuter);
    delete itemOuter;
    this->deleteLater();
}
