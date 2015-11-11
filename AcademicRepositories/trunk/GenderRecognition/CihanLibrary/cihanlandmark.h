#ifndef EXTRACTLANDMARKS_H
#define EXTRACTLANDMARKS_H
#include "cihan_global.h"

namespace cv{
class Mat;
template <typename> class Rect_;
typedef Rect_<int> Rect;
template <typename> class Size_;
typedef Size_<int> Size;
}
class QFileInfo;
namespace CihanLib {
typedef cv::Mat LandmarkMat;
class LandmarkPrivate;
class CIHANLIBRARYSHARED_EXPORT CLandmark
{
public:
    static LandmarkMat extractFaceAndLandmarks(cv::Mat frame, cv::Rect& faceRect);
    static cv::Mat alignImage(cv::Mat frame, LandmarkMat goldenLandmarks);

    CLandmark();
    CLandmark(cv::Mat faceImage);
    CLandmark(QFileInfo fileInfo);
    CLandmark(const char* filepath);
    CLandmark(const CLandmark& other);
    ~CLandmark();
    CLandmark alignTo(const CLandmark alignImage);
    cv::Mat operator () () const;
    CLandmark& operator = (const CLandmark& other);
    CLandmark& operator = (const cv::Mat& mat);
    LandmarkMat landmarks() const;
private:
    LandmarkPrivate*d;
};
}
#endif // EXTRACTLANDMARKS_H
