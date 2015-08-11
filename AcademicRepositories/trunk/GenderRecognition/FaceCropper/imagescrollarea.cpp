#include "imagescrollarea.h"
#include <QLabel>
#include <QLayout>
ImageScrollArea::ImageScrollArea(QWidget* parent):
    QScrollArea(parent)
{
}

ImageScrollArea::~ImageScrollArea()
{

}

void ImageScrollArea::addImage(QImage image)
{
    if (!widget()) {
        setWidget(new QWidget());
    }
    if (!widget()->layout()) {
        widget()->setLayout(new QHBoxLayout());
    }
    QLabel* child = new QLabel(this);
    child->setPixmap(QPixmap::fromImage(image));
    widget()->layout()->addWidget(child);
    children << child;
}

void ImageScrollArea::clear()
{
    if (!children.isEmpty()) {
        while (!children.isEmpty()) {
            delete children.takeFirst();
        }
    }
    delete widget()->layout();
}
