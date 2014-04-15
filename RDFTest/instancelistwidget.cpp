#include "instancelistwidget.h"
#include "instanceobject.h"
#include "imageobject.h"
class InstanceObjectWidgetItem:public QListWidgetItem {
    InstanceObject* instanceObject;
public:
    InstanceObject* get() const {this->instanceObject;}
    InstanceObjectWidgetItem(InstanceObject* instanceObject):instanceObject(instanceObject){this->setText(instanceObject->name());}
};

InstanceListWidget::InstanceListWidget(QWidget *parent) :
    QListWidget(parent)
{
}

void InstanceListWidget::set(ImageObject *im)
{
    this->clear();
    int nInstances = im->count();
    for (int idx=0; idx<nInstances; ++idx) {
        InstanceObject* in = im->at(idx);
        if (in)
            this->addItem(new InstanceObjectWidgetItem(in));
    }
}
