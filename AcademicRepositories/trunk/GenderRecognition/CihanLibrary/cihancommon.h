#ifndef COMMON_H
#define COMMON_H
#include "cihan_global.h"
namespace cv{
class Mat;
template <typename> class Scalar_;
typedef Scalar_<double> Scalar;
}
namespace CihanLib {

typedef cv::Mat LandmarkMat;
class CIHANLIBRARYSHARED_EXPORT CCommon {
public:
    static void showLandmarks(const LandmarkMat points, cv::Mat& img, cv::Scalar color );
};
}
#endif // COMMON_H

