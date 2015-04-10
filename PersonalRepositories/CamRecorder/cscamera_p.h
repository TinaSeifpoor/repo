#ifndef CSCAMERA_P_H
#define CSCAMERA_P_H
#include <QObject>
#include <QImage>
#include "cscamera.h"


class CSCameraPrivate : public QObject
{
    Q_OBJECT
public:
    CSCameraPrivate(CSCamera* cam, CSCamera* parent=0, QRect rect=QRect()):p(cam),gp(parent),rect(rect){
        if (parent) {
            connect(parent, SIGNAL(updated(CSImage)), SLOT(parentUpdated(CSImage)));
        }
    }
    QRect rect;
    CSImage currentImage;
    CSCamera *p;
    CSCamera *gp;
public slots:
    void parentUpdated(CSImage parentImage) {
        p->imageUpdated(parentImage.copy(rect));
    }


};

#endif // CSCAMERA_P_H

