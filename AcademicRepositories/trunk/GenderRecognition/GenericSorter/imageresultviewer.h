#ifndef IMAGERESULTVIEWER_H
#define IMAGERESULTVIEWER_H

#include <QListWidget>
#include <QDir>
#include <QFlags>
class VisionItem;
class ImageResultViewer : public QListWidget
{
    Q_OBJECT

public:

    explicit ImageResultViewer(QWidget *parent = 0);
    ~ImageResultViewer();
    void setDir(QString path);
    QDir dir() const;
    void clear();
    QList<VisionItem *> selectedVisionItems();
    void received(VisionItem *item);

public slots:
    void refresh();

protected:
    void wheelEvent(QWheelEvent *w);

private:
    QHash<VisionItem*, QListWidgetItem*> items;
    QDir __dir;
};

#endif // IMAGERESULTVIEWER_H
