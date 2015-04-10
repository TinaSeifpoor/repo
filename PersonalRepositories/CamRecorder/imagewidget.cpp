#include "imagewidget.h"
#include <QGraphicsItem>
class ImageWidgetPrivate
{
public:
    QGraphicsPixmapItem imageItem;
    QList<QGraphicsRectItem*> rectangles;
};

ImageWidget::ImageWidget(QObject *parent) : QGraphicsScene(parent),d(new ImageWidgetPrivate)
{
    addItem(&d->imageItem);
    d->imageItem.setPos(0,0);
    setSceneRect(d->imageItem.boundingRect());
}

void ImageWidget::setImage(CSImage im)
{
    d->imageItem.setPixmap(QPixmap::fromImage(im.im()));
    setSceneRect(d->imageItem.boundingRect());
}

