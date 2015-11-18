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
namespace std{
template<class _Ty,class _Ax = allocator<_Ty> >class vector;
}
class QFileInfo;
namespace CihanLib {
typedef cv::Mat LandmarkMat;
typedef cv::Mat AffineMat;
class LandmarkPrivate;
class CGoldenLandmark;
class CIHANLIBRARYSHARED_EXPORT CLandmark
{
public:
    static LandmarkMat extractFaceAndLandmarks(cv::Mat frame, cv::Rect& faceRect);
    static cv::Mat alignImage(const cv::Mat frame, const CGoldenLandmark goldenLandmarks);
    static AffineMat alignLandmark(const LandmarkMat from, const LandmarkMat to);
    static cv::Mat maskImage(const cv::Mat frame, const cv::Mat mask);
    static cv::Mat lbpImage(const cv::Mat frame, const cv::Mat mask);
    static LandmarkMat generalizedProcrustes(std::vector<LandmarkMat> landmarks);

    CLandmark();
    CLandmark(cv::Mat faceImage);
    CLandmark(QFileInfo fileInfo);
    CLandmark(const char* filepath);
    CLandmark(const CLandmark& other);
    ~CLandmark();
    cv::Mat alignTo(const CGoldenLandmark goldenLandmark);
    cv::Mat operator () () const;
    CLandmark& operator = (const CLandmark& other);
    CLandmark& operator = (const cv::Mat& mat);
    LandmarkMat landmarks() const;
private:
    LandmarkPrivate*d;
};
}
#endif // EXTRACTLANDMARKS_H
