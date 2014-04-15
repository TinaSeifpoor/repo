#ifndef CLASSOBJECT_H
#define CLASSOBJECT_H
#include <QString>
class ClassObjectPrivate;
class ImageObject;
class ClassObject
{
public:
    ClassObject(QString name);
    void addImage(QString path);
    void removeImage(QString path);
    void removeImage(int idx);

    ImageObject* at(int idx);

    int count() const;

    void clear();

    QString name() const;

private:
    friend class ClassObjectPrivate;
    ClassObjectPrivate* d;
};

#endif // CLASSOBJECT_H
