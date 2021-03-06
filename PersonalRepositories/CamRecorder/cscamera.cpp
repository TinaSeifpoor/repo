#include "cscamera.h"
#include "cscamera_p.h"
#include <QMetaObject>


CSCamera::CSCamera(CSCamera *parent, QRect rect) : QObject(parent), d(new CSCameraPrivate(this,parent,rect))
{

}

CSCamera::~CSCamera() {
    delete d;
}

void CSCamera::imageUpdated(CSImage image)
{
    d->currentImage=image;
    emit updated();
    emit updated(image);
}


