#include "maulanimation.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QColor>
MaulAnimation::MaulAnimation(QRegion reg, QGraphicsScene *scene){
    QPen pen;
    pen.setStyle(Qt::NoPen);
    QRect maulRect = reg.boundingRect();
    QPixmap pim(":/images/Maul");
    item = scene->addPixmap(pim.scaled(maulRect.size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    item->setPos(maulRect.topLeft());
}

void MaulAnimation::deleteLine()
{
    if (item)
        if (item->scene())
            item->scene()->removeItem(item);
    this->deleteLater();
    delete item;
}
