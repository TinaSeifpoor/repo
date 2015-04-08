#include "cscamera.h"
#include "cscamera_p.h"
CSCamera::CSCamera(CSCamera *parent, QRect rect) : QObject(parent), d(new CSCameraPrivate(this,parent,rect))
{

}

CSCamera::~CSCamera() {
    delete d;
}

void CSCamera::imageUpdated(QImage image)
{
    d->currentImage=image;
    emit updated();
    emit updated(image);
}


