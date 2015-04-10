#include "csimage.h"
#include "opencv2/opencv.hpp"
#include <QImage>
#define constructPrivate \
    d = QExplicitlySharedDataPointer<CSImagePrivate>(new CSImagePrivate);
class ImageScaleConverter
{
public:
    ImageScaleConverter() {
        __minVal = 0;
        __rangeVal = 255;
    }
    ImageScaleConverter(int minVal, int rangeVal): __minVal(minVal),__rangeVal(rangeVal){}

    void setMin(int min) {__minVal=min;}
    void setRange(int range) {__rangeVal=range;}

    double convertValue(unsigned int grayValue) const
    {
        double out = grayValue;
        out/=255.0;
        out*=__rangeVal;
        return out+__minVal;
    }

private:
    int __minVal;
    int __rangeVal;
};

class CSImagePrivate : public QSharedData
{
public:
    CSImagePrivate(){}
    void setConverterMin(int min) {c.setMin(min);}
    void setConverterRange(int range){c.setRange(range);}
    void setConverter(int min, int range){c = ImageScaleConverter(min,range);}

    void updateImage(QImage image) {
        __image = image;
    }

    QImage image() const {return __image;}

private:
    ImageScaleConverter c;
    QImage __image;
    cv::Mat integralImage;
};

CSImage::CSImage()
{
    constructPrivate
}

CSImage::CSImage(QImage im)
{
    constructPrivate
    d->updateImage(im);
}

CSImage::CSImage(QString path)
{
    constructPrivate

    d->updateImage(QImage(path));
}

CSImage::CSImage(const CSImage &other)
{
    this->d = other.d;
}

const CSImage &CSImage::operator =(const CSImage &other)
{
    this->d = other.d;
    return *this;
}

QImage CSImage::im() const
{
    return d->image();
}

void CSImage::setInt(int min, int max)
{
    d->setConverter(min,max);
}

CSImage CSImage::copy(const QRect rect) const
{
    CSImage im = *this;
    im.d->updateImage(d->image().copy(rect));
    return im;
}

bool CSImage::isNull() const
{
    return d->image().isNull();
}

CSImage::~CSImage()
{

}


