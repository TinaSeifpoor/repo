#include "imagewidget.h"

ImageWidget::ImageWidget(QWidget *parent) : QLabel(parent)
{

}

void ImageWidget::setImage(QImage im)
{
    setPixmap(QPixmap::fromImage(im));
    resize(im.size());
}

