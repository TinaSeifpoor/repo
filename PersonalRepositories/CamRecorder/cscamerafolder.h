#ifndef CSCAMERAFOLDER_H
#define CSCAMERAFOLDER_H

#include "cscamera.h"
#include <QDir>
#include <QUrl>
#include <QFileInfo>
class CSCameraFolderPrivate;
class CSCameraFolder : public CSCamera
{
    Q_OBJECT
    CSCameraFolderPrivate*d;
    friend class CSCameraFolderPrivate;
public:
    explicit CSCameraFolder(QString path  );
    explicit CSCameraFolder(QDir path     );
    explicit CSCameraFolder(QFileInfo path);
    explicit CSCameraFolder(QUrl path     );

    explicit CSCameraFolder(CSCameraFolder* parent=0, QRect rect = QRect());

public slots:
    void setPath(QString path);
    void setPath(QDir path);
    void setPath(QFileInfo path);
    void setPath(QUrl path);

};

#endif // CSCAMERAFOLDER_H
