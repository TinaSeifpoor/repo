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
    enum Behaviour
    {
        CopyOnReceive=1,
        RemoveOnSend=2
    };
    Q_DECLARE_FLAGS(BehaviourEnum, ImageResultViewer::Behaviour)
    explicit ImageResultViewer(QWidget *parent = 0);
    ~ImageResultViewer();
    void setDir(QString path);
    void sendLeft(QListWidgetItem* widgetItem);
    void sendRight(QListWidgetItem* widgetItem);

    void setBehaviourEnum(BehaviourEnum val);

signals:
    void sendLeftSignal(VisionItem*);
    void sendRightSignal(VisionItem*);

public slots:
    void received(VisionItem* item);
private slots:
    void sendLeftTriggered();
    void sendRightTriggered();

private:
    QHash<VisionItem*, QListWidgetItem*> items;
    QDir dir;
    BehaviourEnum behaviour;
};

#endif // IMAGERESULTVIEWER_H
