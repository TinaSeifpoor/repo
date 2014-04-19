#include "instancelistwidget.h"
#include "instanceobject.h"
#include "imageobject.h"
#include "common.h"
#include "imagewindow.h"
#include "xml.h"
#include <QAction>
#include <QApplication>
#include <QClipboard>

class InstanceObjectWidgetItem:public QListWidgetItem {
    InstanceObject* instanceObject;
public:
    InstanceObject* get() const {return this->instanceObject;}
    InstanceObjectWidgetItem(InstanceObject* instanceObject):instanceObject(instanceObject){this->setText(instanceObject->name());}
};

InstanceListWidget::InstanceListWidget(QWidget *parent) :
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
     connect (this, SIGNAL(currentRowChanged(int)), this, SLOT(on_selectItem(int)));
     connect (this, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(on_itemChanged(QListWidgetItem*)));
}

void InstanceListWidget::add(InstanceObject *obj)
{
    this->parent->addInstance(obj);
    this->set(this->parent);
}

void InstanceListWidget::set(ImageObject *im)
{
    this->parent = im;
    this->clear();
    int nInstances = im->count();
    for (int idx=0; idx<nInstances; ++idx) {
        InstanceObject* in = im->at(idx);
        if (in) {
            InstanceObjectWidgetItem* widgetItem = new InstanceObjectWidgetItem(in);
            widgetItem->setFlags(widgetItem->flags() | Qt::ItemIsEditable);
            this->addItem(widgetItem);
        }
    }
}

void InstanceListWidget::setImageWindow(ImageWindow *iw)
{
    this->iw = iw;
}

void InstanceListWidget::on_copy_triggered()
{
    if(!this->selectedItems().isEmpty()) {
        QVariantHash data;
        foreach (QListWidgetItem* item, this->selectedItems()) {
            InstanceObject* obj = static_cast<InstanceObjectWidgetItem*>(item)->get();
            data.insert(obj->name(),obj->toHash());
        }
        QString dataText;
        XML::writeXMLData(dataText, data);
        QApplication::clipboard()->setText(dataText);
    }
}

void InstanceListWidget::on_paste_triggered()
{
    QString string = QApplication::clipboard()->text();
    QVariantHash data;
    XML::readXMLData(string, &data);
    if (!data.isEmpty()) {
        QStringList keyList = data.keys();
        foreach (QString key, keyList) {
            InstanceObject* obj = new InstanceObject(this->parent->image(), data.value(key).toHash());
            this->add(obj);
        }
    }
}

void InstanceListWidget::on_selectItem(int row)
{
    if (row>-1) {
        InstanceObject* obj = dynamic_cast<InstanceObjectWidgetItem*>(this->item(row))->get();
        KeyPoints k;
        k.push_back(obj->getKeyPoint());
        this->iw->showImageNKeypoints(obj->getSourceImage(), k);
    }
}



void InstanceListWidget::on_itemChanged(QListWidgetItem *item)
{
    InstanceObject* obj = static_cast<InstanceObjectWidgetItem*>(item)->get();
    obj->setName(item->text());
}
