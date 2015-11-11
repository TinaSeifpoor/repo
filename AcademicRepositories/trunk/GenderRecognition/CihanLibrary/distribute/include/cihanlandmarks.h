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
typedef cv::Mat Landmarks;
class FaceLandmarksPrivate;
class CIHANLIBRARYSHARED_EXPORT FaceLandmarks
{
public:
    static Landmarks extractFaceAndLandmarks(cv::Mat frame, cv::Rect& faceRect);
    static cv::Mat alignImage(cv::Mat frame, Landmarks goldenLandmarks);

    FaceLandmarks(cv::Mat faceImage);
    FaceLandmarks(const FaceLandmarks& other);
    ~FaceLandmarks();
    FaceLandmarks alignTo(const FaceLandmarks alignImage);
    cv::Mat operator () () const;
    void operator = (const FaceLandmarks& other);
    Landmarks landmarks() const;
private:
    FaceLandmarksPrivate*d;
};

#endif // EXTRACTLANDMARKS_H
