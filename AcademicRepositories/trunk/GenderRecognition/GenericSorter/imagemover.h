#ifndef IMAGEMOVER_H
#define IMAGEMOVER_H

#include <QWidget>

namespace Ui{
class ImageMover;
}

class VisionItem;
class ImageMover : public QWidget
{
    Q_OBJECT
public:
    explicit ImageMover(QWidget *parent = 0);
    ~ImageMover();
    void setPath(QString path);
    void setRightShortcut(QKeySequence rightShortcut);
    void setLeftShortcut(QKeySequence leftShortcut);

signals:
// Signals going outside
    void sendLeftSignal(VisionItem*);
    void sendRightSignal(VisionItem*);
// Signals passed to inside
    void received(VisionItem *item);
public slots:
    void leChanged();


private:
    Ui::ImageMover* ui;
};

#endif // IMAGEMOVER_H
