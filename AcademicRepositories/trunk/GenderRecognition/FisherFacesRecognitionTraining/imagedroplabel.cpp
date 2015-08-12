#include "imagedroplabel.h"
#include <QDropEvent>
#include <QFileInfo>
#include <QUrl>
#include <QDir>
ImageDropLabel::ImageDropLabel(QWidget *parent) : QLabel(parent)
{
    setAcceptDrops(true);
}

QList<QImage> ImageDropLabel::getImages() const
{
    return images;
}

void ImageDropLabel::dropEvent(QDropEvent* event)
{
    files.clear();
    images.clear();
    foreach (QUrl url, event->mimeData()->urls()) {
        addData(url);
    }
    emit dataChanged();
}

void ImageDropLabel::dragEnterEvent(QDragEnterEvent* event)
{
    event->accept();
    qDebug("drag accepted");
    return;
}

void ImageDropLabel::addData(QUrl url)
{
    QFileInfo urlInfo(url.toLocalFile());
    if (urlInfo.exists()) {
        if (urlInfo.isDir()) {
            addDir(urlInfo);
        } else {
            addFile(urlInfo);
        }
    }
}

void ImageDropLabel::addFile(QFileInfo fileInfo)
{
    QImage image(fileInfo.filePath());
    if (!image.isNull()) {
        images << image;
        files << fileInfo;
    }
}

void ImageDropLabel::addDir(QFileInfo dirInfo)
{
    QDir dir(dirInfo.filePath());
    foreach (QFileInfo subDirInfo, dir.entryInfoList(QDir::Dirs|QDir::NoDotAndDotDot))
        addDir(subDirInfo);
    foreach (QFileInfo fileInfo, dir.entryInfoList(QDir::Files|QDir::NoDotAndDotDot))
        addFile(fileInfo);
}

