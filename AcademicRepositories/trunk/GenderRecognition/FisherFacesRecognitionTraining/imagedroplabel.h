#ifndef IMAGEDROPLISTWIDGET_H
#define IMAGEDROPLISTWIDGET_H

#include <QLabel>
class QUrl;
class QFileInfo;
class ImageDropLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ImageDropLabel(QWidget *parent = 0);

    QList<QImage> getImages() const;

protected:
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);

    void addData(QUrl url);
    void addDir(QFileInfo dirInfo);
    void addFile(QFileInfo fileInfo);
signals:
    void dataChanged();

private:
    QList<QFileInfo> files;
    QList<QImage> images;
};

#endif // IMAGEDROPLISTWIDGET_H
