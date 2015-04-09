#include "cvqtconversion.h"
#include "opencv2/opencv.hpp"
#include <QImage>
cv::Mat CVQtConversion::convert(QImage img)
{
    return cv::Mat(img.height(),img.size().width(),1,(uchar*)img.data_ptr(),img.bytesPerLine());
}

QImage CVQtConversion::convert(cv::Mat img)
{
    return QImage((uchar*) img.data, img.cols, img.rows, (int)img.step, QImage::Format_RGB888);
}
