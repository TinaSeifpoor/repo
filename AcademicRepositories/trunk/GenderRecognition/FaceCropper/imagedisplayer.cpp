#include "imagedisplayer.h"
#include "common.h"
#include "ui_imagedisplayer.h"

ImageDisplayer::ImageDisplayer(QImage leftImage, QList<QImage> rightImages, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageDisplayer),
    image(leftImage)
{
    ui->setupUi(this);
    ui->lblLeftImage->setPixmap(QPixmap::fromImage(leftImage));
    setRightImages(rightImages);
}

ImageDisplayer::~ImageDisplayer()
{
    delete ui;
}

void ImageDisplayer::setRightImages(QList<QImage> rightImages)
{
    ui->scrollArea->clear();
    foreach (QImage rightImage, rightImages) {
        ui->scrollArea->addImage(rightImage);
    }
}
