#include "cihanlbp.h"
#include "lbp.hpp"
namespace CihanLib{


Mat CLBP::OLBP(const Mat& src)
{
    return lbp::OLBP(src);
}

Mat CLBP::ELBP(const Mat& src, int radius, int neighbors)
{
    return lbp::ELBP(src,radius,neighbors);
}

Mat CLBP::VARLBP(const Mat& src, int radius, int neighbors)
{
    return lbp::VARLBP(src,radius,neighbors);
}

void CLBP::OLBP(const Mat& src, Mat& dst)
{
    lbp::OLBP(src,dst);
}

void CLBP::ELBP(const Mat& src, Mat& dst, int radius, int neighbors)
{
    lbp::ELBP(src,dst,radius,neighbors);
}

void CLBP::VARLBP(const Mat& src, Mat& dst, int radius, int neighbors)
{
    lbp::VARLBP(src,dst,radius,neighbors);
}

Mat CLBP::extractFeaturesOLBP(const Mat& src, int threshold, int nRowCells, int nColCells)
{
    cv::Mat dst = OLBP(src);
    dst = dst>threshold;
    int nRowSteps = dst.rows / 8;
    for (int idxRow=0; idxRow=)
}
}
