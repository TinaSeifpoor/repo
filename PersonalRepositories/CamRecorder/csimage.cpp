#include "csimage.h"
#include "opencv2/opencv.hpp"
#include <QImage>
class CSImagePrivate
{
public:
    CSImagePrivate(CSImage*p):p(p){}
    CSImage*p;
    int __minVal;
    int __rangeVal;
    QImage __image;
    cv::Mat integralImage;
};

CSImage::CSImage(QImage im):
    d(new CSImagePrivate(this))
{
    d->__image=im;
    d->__minVal=0;
    d->__rangeVal=255;
}

QImage CSImage::im() const
{
    return d->__image;
}

void CSImage::setInt(int min, int max)
{
    d->__minVal = min;
    d->__rangeVal  = max-min;
}

double CSImage::convertValue(unsigned int grayValue) const
{
    double out = grayValue;
    out/=255.0;
    out*=d->__rangeVal;
    return out+d->__minVal;
}
