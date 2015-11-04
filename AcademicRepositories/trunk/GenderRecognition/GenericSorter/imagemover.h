#ifndef IMAGEMOVER_H
#define IMAGEMOVER_H

#include <QWidget>

class ImageResultViewer;
class VisionItem;
class QLineEdit;

class ImageMover : public QWidget
{
    Q_OBJECT
public:
    explicit ImageMover(QWidget *parent = 0);
    void setPath(QString path);

signals:
// Signals going outside
    void sendLeftSignal(VisionItem*);
    void sendRightSignal(VisionItem*);
// Signals passed to inside
    void received(VisionItem *item);
public slots:
    void leChanged();
private:
    QLineEdit* le;
    ImageResultViewer* irv;
};

#endif // IMAGEMOVER_H
