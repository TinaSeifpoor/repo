#ifndef COMMON_H
#define COMMON_H
#include "opencv2/opencv.hpp"
typedef std::vector<cv::KeyPoint> KeyPoints;
typedef cv::Mat Image;
class QString;
class Common {
public:
static QString mat2ByteArray(const Image &image);
static Image byteArray2Mat(const QString & string);
}
;
#endif // COMMON_H
