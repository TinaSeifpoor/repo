#include "maulanimation.h"
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QColor>
MaulAnimation::MaulAnimation(QRegion reg, QGraphicsScene *scene){
    QPen pen;
    pen.setStyle(Qt::NoPen);
    QRect ellipseRect = reg.boundingRect();
    QRadialGradient gradient(ellipseRect.center(), ellipseRect.width()/2,
                             ellipseRect.center());
    gradient.setColorAt(1, QColor::fromRgbF(.6,.8,.6, 0.6));
    gradient.setColorAt(0, QColor::fromRgbF(.2,.4,.2,.6));
    QBrush brush(gradient);
    item = scene->addEllipse(reg.boundingRect(),pen, brush);
}

void MaulAnimation::deleteLine()
{
    item->scene()->removeItem(item);
    delete item;
    this->deleteLater();
}
