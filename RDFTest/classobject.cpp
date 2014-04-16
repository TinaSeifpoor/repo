#include "classobject.h"
#include "imageobject.h"
#include <QVector>
#include <QHash>
#include <QStringList>
class ClassObjectPrivate {
public:
    QHash<QString,ImageObject*> imageList;
    QString className;
};

ClassObject::ClassObject(QString name):d(new ClassObjectPrivate)
{
    d->className = name;
}

ClassObject::ClassObject(QVariantHash ini):d(new ClassObjectPrivate)
{
    d->className = ini.value("Name").toString();
    QVariantHash imageListHash = ini.value("ImageList").toHash();
    QStringList keyList = imageListHash.keys();
    foreach (QString key, keyList) {
        ImageObject* obj = new ImageObject(imageListHash.value(key).toHash());
        d->imageList.insert(key, obj);
    }
}

void ClassObject::addImage(QString path)
{
    if (!d->imageList.contains(path))
        d->imageList.insert(path, new ImageObject(path));
}


QString ClassObject::name() const
{
    return d->className;
}

void ClassObject::setName(QString newName)
{
    d->className = newName;
}

QVariantHash ClassObject::toIni() const
{
    QVariantHash output;
    QStringList keys = d->imageList.keys();
    QVariantHash classHash;
    classHash.insert("Name", this->name());
    QVariantHash imageListHash;

    foreach (QString key, keys) {
        imageListHash.insertMulti(key, d->imageList.value(key)->toIni());
    }
    classHash.insert("ImageList", imageListHash);
    output.insert(this->name(),classHash);
    return output;
}

ImageObject* ClassObject::at(int idx)
{
    QString key = d->imageList.keys().at(idx);
    return d->imageList.value(key);
    if (d->imageList.size()< idx && idx>-1)
        return d->imageList.value(d->imageList.keys()[idx]);
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

