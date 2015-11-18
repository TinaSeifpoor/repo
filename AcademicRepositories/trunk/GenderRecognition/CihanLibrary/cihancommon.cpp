#include "cihancommon.h"
#include "opencv2/opencv.hpp"
#include "cihanlandmark.h"
using namespace CihanLib;


void CCommon::showLandmarks(const LandmarkMat points, cv::Mat& img, cv::Scalar color)
{
    using namespace cv;
    std::vector<Point2f> vec;
    points.copyTo( vec );

    for(vector<Point2f>::const_iterator it = vec.begin(); it!=vec.end(); ++it) {
        Point2f p = *it;
        circle( img, p, 2, color, 2 );
    }
}
