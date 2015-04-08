#ifndef CSCAMERA_H
#define CSCAMERA_H

#include <QObject>
#include <QImage>
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
    void updated(QImage image);

public slots:
    virtual void imageUpdated(QImage image);
};

#endif // CSCAMERA_H
