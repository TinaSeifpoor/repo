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

//#include "histogram.hpp"

//Mat CLBP::extractFeaturesOLBP(const Mat& src, int threshold, int nRowCells, int nColCells)
//{
//    cv::Mat dst = OLBP(src);
//    dst = dst>threshold;
//    int nRowSteps = ceil((float)dst.rows / nRowCells);
//    int nColSteps = ceil((float)dst.cols / nColCells);
//    for (int idxRow=0; idxRow<nRowSteps; ++idxRow) {
//        for (int idxCol=0; idxCol<nColSteps; ++idxCol) {
//            int left   = (idxRow+1)*nRowCells;
//            int top    = (idxCol+1)*nColCells;
//            int right  = qMin(left+nRowCells,dst.rows);
//            int bottom = qMin(top+nColCells,dst.cols);
//            cv::Rect roi = cv::Rect(left,top,right-left, bottom-top);
//            cv::Mat part = src(roi);
//            int nZeroes=0;
//            for (int idxPixel = 0; idxPixel<part.size; ++idxPixel) {
//                if (!part[idxPixel])
//                    ++nZeroes;
//            }

//        }
//    }
//}
}
