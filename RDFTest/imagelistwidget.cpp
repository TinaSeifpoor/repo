#include "imagelistwidget.h"
#include "classobject.h"
#include "imageobject.h"
#include "imagewindow.h"
#include "instancelistwidget.h"
#include "xml.h"
#include <QAction>
#include <QApplication>
#include <QClipboard>

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
    QAction* copy = new QAction(this);
    QAction* paste = new QAction(this);
    copy->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    paste->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_V));
    this->addAction(copy);
    this->addAction(paste);
    connect (copy, SIGNAL(triggered()), this, SLOT(on_copy_triggered()));
    connect (paste, SIGNAL(triggered()), this, SLOT(on_paste_triggered()));

    connect (this, SIGNAL(currentRowChanged(int)), this, SLOT(on_currentRowChanged(int)));
}

void ImageListWidget::set(ClassObject *obj)
{
    this->parent = obj;
    this->clear();
    int nImages = obj->count();
    for (int idx=0; idx<nImages; ++idx) {
        ImageObject* im = obj->at(idx);
        if (im) {
            ImageObjectWidgetItem* it = new ImageObjectWidgetItem(im);
            it->setFlags(it->flags() | Qt::ItemIsEditable);
            this->addItem(it);
        }
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
    this->parent->addImage(imagePath);
    reload();
}

void ImageListWidget::add(ImageObject *im)
{
    this->parent->addImage(im);
    reload();
}

void ImageListWidget::on_currentRowChanged(int row)
{
    if (row!=-1) {
    ImageObject* i = this->getImage(row);
    this->ilw->set(i);
    this->iw->showImage(i->image());
    }
}

void ImageListWidget::on_copy_triggered()
{
    if(!this->selectedItems().isEmpty()) {
        QVariantHash data;
        foreach (QListWidgetItem* item, this->selectedItems()) {
            ImageObject* obj = static_cast<ImageObjectWidgetItem*>(item)->get();
            data.unite(obj->toHash());
        }
        QString dataText;
        XML::writeXMLData(dataText, data);
        QApplication::clipboard()->setText(dataText);
    }
}

void ImageListWidget::on_paste_triggered()
{
    QString string = QApplication::clipboard()->text();
    QVariantHash data;
    XML::readXMLData(string, &data);
    if (!data.isEmpty()) {
        QStringList keyList = data.keys();
        foreach (QString key, keyList) {
            ImageObject* obj = new ImageObject(data.value(key).toHash());
            this->add(obj);
        }
    }
}

void ImageListWidget::reload()
{
    this->set(this->parent);
}

ImageObject* ImageListWidget::getImage(int row)
{
    ImageObjectWidgetItem* item = static_cast<ImageObjectWidgetItem*>(this->item(row));
    return item->get();
}


void ImageListWidget::on_itemChanged(QListWidgetItem *item)
{
    ImageObject* obj = static_cast<ImageObjectWidgetItem*>(item)->get();
    obj->setName(item->text());
}
