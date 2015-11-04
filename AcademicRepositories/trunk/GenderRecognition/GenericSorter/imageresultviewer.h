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
    void sendLeft(QListWidgetItem* widgetItem);
    void sendRight(QListWidgetItem* widgetItem);
    void clear();

signals:
    void sendLeftSignal(VisionItem*);
    void sendRightSignal(VisionItem*);

public slots:
    void received(VisionItem* item);
    void refresh();

private slots:
    void sendLeftTriggered();
    void sendRightTriggered();

private:
    QHash<VisionItem*, QListWidgetItem*> items;
    QDir __dir;
};

#endif // IMAGERESULTVIEWER_H
