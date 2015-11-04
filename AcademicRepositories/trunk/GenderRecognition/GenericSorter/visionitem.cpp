#include "visionitem.h"
#include <QDir>
VisionItem::VisionItem(QFileInfo fileInfo)
{
    setFileInfo(fileInfo);
    setName(FileInfo().baseName());
    setIcon(QIcon(FileInfo().filePath()));
}

void VisionItem::moveTo(QString path)
{
    QString to = QDir(path).filePath(FileInfo().fileName());
    QString from = FileInfo().filePath();
    if (QFile::copy(FileInfo().filePath(), to)) {
        qDebug("Success: %s to %s", from.toLatin1().constData(), to.toLatin1().constData());
        QFile::remove(FileInfo().filePath());
        setFileInfo(to);
    } else {
        qWarning("Failed: %s to %s", from.toLatin1().constData(), to.toLatin1().constData());
    }

}
