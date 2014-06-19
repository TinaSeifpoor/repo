#ifndef RDFOBJECT_H
#define RDFOBJECT_H
#include <QHash>
class RDFObject
{
public:
    virtual QString name() const;
    virtual RDFObject* at(int idx);
    virtual int count() const;
    virtual bool isValid() const;
    virtual QHash<QString,RDFObject*> all() const;
};

#endif // RDFOBJECT_H
