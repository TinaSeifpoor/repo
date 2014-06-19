#ifndef MYCLASSOBJECT_H
#define MYCLASSOBJECT_H
#include "classobject.h"
class MyClassObjectPrivate;
class MyClassObject : public ClassObject
{
public:
    MyClassObject(QString name);
private:
    friend class MyClassObjectPrivate;
    MyClassObjectPrivate* d;
};

#endif // MYCLASSOBJECT_H
