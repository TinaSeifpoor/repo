#ifndef IMAGEMOVER_H
#define IMAGEMOVER_H

#include <QWidget>

namespace Ui{
class ImageMover;
}

class VisionItem;
class ImageMoverPrivate;
class ImageMover : public QWidget
{
    Q_OBJECT
public:
    explicit ImageMover(QWidget *parent = 0);
    ~ImageMover();
    void setPath(QString path);
    void setShortcut(QKeySequence shortcut, QObject* receiver);

    QString path() const;

signals:
    // Signals going outside
    void sendSignal(VisionItem *item, QObject* receiver);
    // Signals passed to inside
public slots:
    void leChanged();
    // To be called from other movers
    void received(VisionItem *item);

    // Triggered to actuate send action
    void sendTriggered(QObject* receiver);


private:
    Ui::ImageMover* ui;
    ImageMoverPrivate*d;
};

#endif // IMAGEMOVER_H
