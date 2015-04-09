#ifndef CVQTCONVERSION_H
#define CVQTCONVERSION_H
namespace cv {
class Mat;
}
class QImage;
class CVQtConversion
{
public:
    static cv::Mat convert(QImage img);
    static QImage convert (cv::Mat img);
};

#endif // CVQTCONVERSION_H
