#include "classobject.h"
#include "imageobject.h"
#include <QVector>
class ClassObjectPrivate {
public:
    QVector<ImageObject*> imageList;
    QString className;
};

ClassObject::ClassObject(QString name):d(new ClassObjectPrivate)
{
    d->className = name;
}

void ClassObject::addImage(QString path)
{
    d->imageList << new ImageObject(path);
}


QString ClassObject::name() const
{
    return d->className;
}

ImageObject* ClassObject::at(int idx)
{
    if (d->imageList.size()< idx && idx>-1)
        return d->imageList.at(idx);
    return 0;
}

int ClassObject::count() const
{
    return d->imageList.count();
}

void ClassObject::clear()
{
    d->imageList.clear();
}

