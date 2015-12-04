#include "imagewidget.h"
#include <QGraphicsItem>
ImageWidgetFactory f;

class ImageWidgetFactory
{
public:
    QList<ImageWidget*> imageWidgets;
    QHash<ImageWidget*, ImageWidget*> imageWidgetChildren;
};

class ImageWidgetPrivate
{
public:
    QGraphicsPixmapItem imageItem;
    QList<QGraphicsRectItem*> rectangles;
};

ImageWidget::ImageWidget(QObject *parent) : QGraphicsScene(parent),d(new ImageWidgetPrivate)
{
    f.imageWidgets.append(this);
    addItem(&d->imageItem);
    d->imageItem.setPos(0,0);
    setSceneRect(d->imageItem.boundingRect());
}

ImageWidget::~ImageWidget()
{
    f.imageWidgets.removeAll(this);
    delete d;
}

void ImageWidget::setImage(CSImage im)
{
    d->imageItem.setPixmap(QPixmap::fromImage(im.im()));
    setSceneRect(d->imageItem.boundingRect());
}

