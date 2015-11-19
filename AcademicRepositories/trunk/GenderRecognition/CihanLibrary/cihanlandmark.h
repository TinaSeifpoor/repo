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
    static AffineMat alignLandmark(const LandmarkMat from, const LandmarkMat to, double& scale);
    static LandmarkMat generalizedProcrustes(std::vector<LandmarkMat> landmarks);

    CLandmark();
    CLandmark(cv::Mat faceImage);
    CLandmark(QFileInfo fileInfo);
    CLandmark(const char* filepath);
    CLandmark(const CLandmark& other);
    ~CLandmark();
    cv::Mat alignTo(const CGoldenLandmark goldenLandmark, double scaleThresholdMin=.5, double scaleThresholdMax = 2);
    cv::Mat operator () () const;
    CLandmark& operator = (const CLandmark& other);
    CLandmark& operator = (const cv::Mat& mat);
    LandmarkMat landmarks() const;
    bool isValid() const;

private:
    LandmarkPrivate*d;
};
}
#endif // EXTRACTLANDMARKS_H
