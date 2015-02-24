#include "imagewindow.h"
#include <QMouseEvent>
using namespace cv;
ImageWindow::ImageWindow(QWidget* parent) :
    QLabel(parent) {}

void ImageWindow::showImage(Mat im)
{
    Mat rgb;
    if (im.channels()==3)
        cvtColor(im, rgb, CV_BGR2RGB);
    else
        cvtColor(im, rgb, CV_GRAY2RGB);
    QImage imQ((const uchar*)rgb.data, rgb.cols, rgb.rows, rgb.step1(), QImage::Format_RGB888);
    this->setPixmap(QPixmap::fromImage(imQ));
}

void ImageWindow::mouseReleaseEvent(QMouseEvent *ev)
{
    Q_EMIT clicked(ev->x(), ev->y());
    ev->accept();
}
