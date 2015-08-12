#ifndef COMMON_H
#define COMMON_H

#include <QImage>
namespace cv {
class Mat;
}
class QLayout;
class Common
{
public:

    static QImage cvMatToQImage(const cv::Mat& inMat);
    static cv::Mat QImageToCvMat(const QImage& inImage, bool inCloneImageData = true);
    static void clearLayout(QLayout* layout);
};

#endif // COMMON_H
