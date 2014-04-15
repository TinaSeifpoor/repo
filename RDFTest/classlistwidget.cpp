#include "classlistwidget.h"
class ClassObjectWidgetItem:public QListWidgetItem {
    ClassObject* classObject;
public:
    ClassObject* get() const {return this->classObject;}
    void set(ImageListWidget* ilw){ilw->set(classObject);}
    ClassObjectWidgetItem(ClassObject* classObject):classObject(classObject){this->setText(this->classObject->name());}
};

ClassListWidget::ClassListWidget(QWidget *parent):QListWidget(parent)
{
    connect (this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_doubleClicked(QModelIndex)));
}

void ClassListWidget::addClass(QString className)
{
    this->addItem(new ClassObjectWidgetItem(new ClassObject(className)));
}

void ClassListWidget::on_doubleClicked(const QModelIndex &index)
{
    this->imageListWidget->set(this->getClass(index.row()));
}

ClassObject *ClassListWidget::getClass(const QModelIndex &index)
{
    return this->getClass(index.row());
}

ClassObject* ClassListWidget::getClass(int row)
{
    ClassObjectWidgetItem* item = static_cast<ClassObjectWidgetItem*>(this->item(row));
    return item->get();
}

int ClassListWidget::getRowFromName(QString className)
{
    int nItems = this->count();
    for (int idxItem=0; idxItem<nItems; ++idxItem)
    {
        ClassObjectWidgetItem* i = static_cast<ClassObjectWidgetItem*>(this->item(idxItem));
        if (i->get()->name()==className)
        {
            return idxItem;
        }
    }
    return -1;
}


void ClassListWidget::setImageListWidget(ImageListWidget *ilw)
{
    this->imageListWidget = ilw;
}
