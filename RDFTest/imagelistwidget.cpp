#include "imagelistwidget.h"
#include "classobject.h"
#include "imageobject.h"
#include "instancelistwidget.h"
class ImageObjectWidgetItem:public QListWidgetItem {
    ImageObject* imageObject;
public:
    ImageObject* get() const {return this->imageObject;}
    void set(InstanceListWidget* ilw) {ilw->set(imageObject);}
    ImageObjectWidgetItem(ImageObject* imageObject):imageObject(imageObject){this->setText(imageObject->name());}
};

ImageListWidget::ImageListWidget(QWidget *parent) :
    QListWidget(parent)
{
    connect (this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_doubleClicked(QModelIndex)));
}

void ImageListWidget::set(ClassObject *obj)
{
    this->clear();
    int nImages = obj->count();
    for (int idx=0; idx<nImages; ++idx) {
        ImageObject* im = obj->at(idx);
        if (im)
            this->addItem(new ImageObjectWidgetItem(im));
    }
}

void ImageListWidget::setInstanceListWidget(InstanceListWidget *ilw)
{
    this->ilw = ilw;
}

void ImageListWidget::setImageWindow(ImageWindow *iw)
{
    this->iw = iw;
}

void ImageListWidget::add(QString imagePath)
{
    this->add(new ImageObject(imagePath));
}

void ImageListWidget::add(ImageObject* im)
{
    this->addItem(new ImageObjectWidgetItem(im));
}

void ImageListWidget::on_doubleClicked(QModelIndex index)
{
    ImageObject* i = this->getImage(index.row());
    this->ilw->set(i);
    this->iw->showImage(i->image());
}


ImageObject* ImageListWidget::getImage(int row)
{
    ImageObjectWidgetItem* item = static_cast<ImageObjectWidgetItem*>(this->item(row));
    return item->get();
}
