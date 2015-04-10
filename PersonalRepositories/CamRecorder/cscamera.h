#ifndef CSCAMERA_H
#define CSCAMERA_H

#include <QObject>
#include "csimage.h"
class CSCameraPrivate;
class CSCamera : public QObject
{
    Q_OBJECT
    friend class CSCameraPrivate;
    CSCameraPrivate*d;
public:
    explicit CSCamera(CSCamera* parent=0, QRect rect = QRect());
    virtual ~CSCamera();

signals:
    void updated();
    void updated(CSImage image);

public slots:
    virtual void imageUpdated(CSImage image);
};

#endif // CSCAMERA_H
