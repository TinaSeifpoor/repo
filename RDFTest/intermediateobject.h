#ifndef INTERMEDIATEOBJECT_H
#define INTERMEDIATEOBJECT_H
#include "rdfobject.h"
#include <QHash>
namespace cv {
class Mat;
}
class InstanceObject;
class IntermediateObject
{
public:
    IntermediateObject(QString imagePath);
    QString name() const;
    RDFObject* at(int idx);
    int count() const;
    bool isValid() const;
    QHash<QString,RDFObject*> all() const;
    cv::Mat image() const;

private:
    friend class IntermediateObjectPrivate;
    IntermediateObjectPrivate* d;
};

#endif // INTERMEDIATEOBJECT_H
