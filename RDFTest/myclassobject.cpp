#include "myclassobject.h"
#include "intermediateobject.h"
#include <QVector>
#include <QString>
class MyClassObjectPrivate {
public:
    QVector<IntermediateObject*> imageList;
    QString className;
    bool valid;
};

MyClassObject::MyClassObject(QString name):d(new MyClassObjectPrivate)
{
    d->valid = true;
    d->className = name;
}

QString ClassObject::name() const
{
    return d->className;
}

QHash<QString, RDFObject *> MyClassObject::all() const
{

}

RDFObject* MyClassObject::at(int idx)
{
    if (d->imageList.size()< idx && idx>-1)
        return dynamic_cast<RDFObject*>(d->imageList.at(idx));
    return 0;
}

int MyClassObject::count() const
{
    return d->imageList.count();
}

void MyClassObject::clear()
{
    d->imageList.clear();
}


bool MyClassObject::isValid() const
{
    return d->valid;
}
