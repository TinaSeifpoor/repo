#ifndef CSCAMERAFOLDER_P_H
#define CSCAMERAFOLDER_P_H
#include <QDir>
#include <QFileSystemWatcher>
#include <QTimer>
#include "cscamerafolder.h"
class CSCameraFolderPrivate : public QObject
{
    Q_OBJECT
public:
    CSCameraFolder*p;
    CSCameraFolderPrivate(CSCameraFolder* p):p(p),counter(0),timeout(0) {
        connect (&w, SIGNAL(directoryChanged(QString)), SLOT(updateFiles()));
        timeout=900;
    }

    QDir baseDir;
    QFileInfoList files;
    QFileSystemWatcher w;
    uint counter;
    uint timeout;
    QRect subRect;

    void setDir(QDir dir) {
        baseDir = dir;
        w.addPath(dir.path());
        updateFiles();
        sendNext();
    }

public slots:
    void updateFiles() {
        files = baseDir.entryInfoList(QDir::Files|QDir::NoDotAndDotDot);
        // find new files
    }

    void sendNext() {
        int currentIndex = (counter++)%files.count();
        QFileInfo currentFile = files.value(currentIndex);
        QImage image = QImage(currentFile.filePath());

        if (!image.isNull()) {
            p->imageUpdated(image);
#ifdef QT5
            QTimer::singleShot(timeout, Qt::CoarseTimer, SLOT(sendNext()));
#else
            QTimer::singleShot(timeout, this, SLOT(sendNext()));
#endif
        } else {
            QMetaObject::invokeMethod(this, SLOT(sendNext()), Qt::QueuedConnection);
        }
    }

};

#endif // CSCAMERAFOLDER_P_H

