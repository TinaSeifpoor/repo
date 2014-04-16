#include "imagewindow.h"
#include <QMouseEvent>
using namespace cv;
ImageWindow::ImageWindow(QWidget* parent) :
    QLabel(parent) {}

void ImageWindow::showImage(const Image im)
{
    Image rgb;
    if (im.channels()==3)
        cvtColor(im, rgb, CV_BGR2RGB);
    else
        cvtColor(im, rgb, CV_GRAY2RGB);
    QImage imQ((uchar*)rgb.data, rgb.cols, rgb.rows, rgb.step, QImage::Format_RGB888);
    this->setPixmap(QPixmap::fromImage(imQ));
}

void ImageWindow::showImageNKeypoints(const Image im, const KeyPoints keyPoints)
{
    if (im.empty())
        return;
    Image imOut,rgb;
    im.copyTo(imOut);
    drawKeypoints(im, keyPoints, imOut, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    if (imOut.channels()==3)
        cvtColor(imOut, rgb, CV_BGR2RGB);
    else
        cvtColor(imOut, rgb, CV_GRAY2RGB);
    QImage imQ((uchar*)rgb.data, rgb.cols, rgb.rows, rgb.step, QImage::Format_RGB888);
    this->setPixmap(QPixmap::fromImage(imQ));
}

void ImageWindow::mouseReleaseEvent(QMouseEvent *ev)
{
    emit clicked(ev->x(), this->height()-ev->y());
    ev->accept();
}
