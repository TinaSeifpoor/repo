#ifndef CLASSOBJECT_H
#define CLASSOBJECT_H
#include <QVariantHash>

class ClassObjectPrivate;
class ImageObject;
class QString;



class ClassObject
{
public:
    ClassObject(QString name);
    ClassObject(QVariantHash data);
    void addImage(QString path);
    void addImage(ImageObject* im);
    void removeImage(QString path);
    void removeImage(int idx);
    ImageObject* at(int idx);
    int count() const;
    void clear();
    QString name() const;

    void setName(QString newName);

    QVariantHash toHash() const;

private:
    friend class ClassObjectPrivate;
    ClassObjectPrivate* d;
};

#endif // CLASSOBJECT_H
