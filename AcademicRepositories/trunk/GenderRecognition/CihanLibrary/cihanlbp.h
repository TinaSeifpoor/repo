#ifndef CIHANLBP
#define CIHANLBP
#include "cihan_global.h"
namespace cv {
class Mat;
}
namespace CihanLib {
class CIHANLIBRARYSHARED_EXPORT CLBP
{
public:
    static cv::Mat OLBP(const cv::Mat& src);
    static cv::Mat ELBP(const cv::Mat& src, int radius = 1, int neighbors = 8);
    static cv::Mat VARLBP(const cv::Mat& src, int radius = 1, int neighbors = 8);

    static void OLBP(const cv::Mat& src, cv::Mat& dst);
    static void ELBP(const cv::Mat& src, cv::Mat& dst, int radius = 1, int neighbors = 8);
    static void VARLBP(const cv::Mat& src, cv::Mat& dst, int radius = 1, int neighbors = 8);

    static cv::Mat extractFeaturesOLBP(const cv::Mat& src, int threshold=123.0, int nRowCells, int nColCells);

};
}
#endif // CIHANLBP

