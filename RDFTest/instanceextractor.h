#ifndef INSTANCEEXTRACTOR_H
#define INSTANCEEXTRACTOR_H

#include "imageobject.h"
#include "instanceobject.h"
class InstanceExtractor
{
public:
    InstanceExtractor();
    QList<InstanceObject> extract(ImageObject im);
};

#endif // INSTANCEEXTRACTOR_H
