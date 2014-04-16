#include "instancelistwidget.h"
#include "instanceobject.h"
#include "imageobject.h"
#include "common.h"
#include "imagewindow.h"
class InstanceObjectWidgetItem:public QListWidgetItem {
    InstanceObject* instanceObject;
public:
    InstanceObject* get() const {return this->instanceObject;}
    InstanceObjectWidgetItem(InstanceObject* instanceObject):instanceObject(instanceObject){this->setText(instanceObject->name());}
};

InstanceListWidget::InstanceListWidget(QWidget *parent) :
    QListWidget(parent)
{
    connect (this, SIGNAL(currentRowChanged(int)), this, SLOT(on_selectItem(int)));
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

void InstanceListWidget::setImageWindow(ImageWindow *iw)
{
    this->iw = iw;
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
