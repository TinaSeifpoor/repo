#ifndef IMAGEDISPLAYER_H
#define IMAGEDISPLAYER_H

#include <QWidget>

namespace Ui {
class ImageDisplayer;
}

class FaceCropper;

class ImageDisplayer : public QWidget
{
    Q_OBJECT

public:
    explicit ImageDisplayer(QImage leftImage, QList<QImage> rightImages, QWidget *parent = 0);
    ~ImageDisplayer();

    void setRightImages(QList<QImage> rightImages);

    QImage image;

private:
    Ui::ImageDisplayer *ui;
    FaceCropper*faceCropper;
};

#endif // IMAGEDISPLAYER_H
