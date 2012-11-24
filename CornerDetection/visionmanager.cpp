#include "visionmanager.h"
#include <iostream>
#include <fstream>
#include "math.h"
#include "stdio.h"
#include <sstream>
#include <vector>
#include "stdlib.h"

typedef cv::Mat Image;

using namespace cv;
using namespace std;

VisionManager::VisionManager()
{
}

void VisionManager::inspectImageWithHomography(const string &imageFilepath,
                                               const string &homographyFilepath)
{
    Image imSrc = imread(imageFilepath);
    Mat homographyMatrix(3,3,CV_64F);
    ifstream dataFile(homographyFilepath.c_str());
    for (int idxRow=0; idxRow<3; ++idxRow)
    {
        for (int idxCol=0; idxCol<3; ++idxCol)
        {
            double val;
            dataFile >> val;
            homographyMatrix.at<double>(idxRow, idxCol) = val;
        }
    }
    inspectImageWithHomography(imSrc, homographyMatrix);
}

void VisionManager::inspectImageWithHomography(Mat imSrc, Mat homographyMatrix)
{
    HarrisCornerDetector fd;

    Image imMaskSrc, imMaskDst, imDst;
    int nCols = imSrc.cols,
        nRows = imSrc.rows;

    imMaskSrc = Image(nRows, nCols, CV_8UC1, Scalar(255));
    warpPerspective(imMaskSrc, imMaskDst, homographyMatrix, Size(nCols,nRows));
    warpPerspective(imMaskDst, imMaskSrc, homographyMatrix.inv(), Size(nCols,nRows));

    warpPerspective(imSrc, imDst, homographyMatrix, Size(nCols,nRows));

    vector<KeyPoint> keyPointsSrc, keyPointsDst, keyPointsSrc2Dst;
    fd.detect(imSrc, keyPointsSrc, imMaskSrc);
    fd.detect(imDst, keyPointsDst, imMaskDst);
    warpPoint(homographyMatrix, keyPointsSrc, keyPointsSrc2Dst);

    Image imSrcDisp, imDstDisp, imSrc2DstDisp;
    imSrc.copyTo(imSrcDisp);
    imDst.copyTo(imDstDisp);
    imDst.copyTo(imSrc2DstDisp);
    drawOnImage(imSrcDisp, keyPointsSrc);
    drawOnImage(imDstDisp, keyPointsDst);
    drawOnImage(imSrc2DstDisp, keyPointsSrc2Dst);
    imshow("Src", imSrcDisp);
    imshow("Dst", imDstDisp);
    imshow("Src2Dst", imSrc2DstDisp);
    waitKey();
    int a=5;
    a++;
}


void VisionManager::warpPoint(Mat M, const Point2f& src, Point2f& dst){
    Mat srcM(3/*rows*/,1 /* cols */,CV_64F);

    srcM.at<double>(0,0)=src.x;
    srcM.at<double>(1,0)=src.y;
    srcM.at<double>(2,0)=1.0;

    Mat dstM = M*srcM; //USE MATRIX ALGEBRA
    dst = Point2f(dstM.at<double>(0,0)/dstM.at<double>(2,0),dstM.at<double>(1,0)/dstM.at<double>(2,0));
}

void VisionManager::warpPoint(Mat H, vector<KeyPoint> &src, vector<KeyPoint> &dst)
{
    dst.clear();
    for (unsigned int idx=0; idx<src.size(); ++idx)
    {
        KeyPoint srcKeyPoint = src[idx];
        Point2f dstPoint;
        warpPoint(H, srcKeyPoint.pt, dstPoint);
        dst.insert(dst.end(), KeyPoint(dstPoint, srcKeyPoint.size, srcKeyPoint.angle, srcKeyPoint.response, srcKeyPoint.octave, srcKeyPoint.class_id));
    }
}

double VisionManager::measureRepeatability(const vector<KeyPoint>& keypoints1, const vector<KeyPoint>& keypoints2, const Mat& homography1to2, const Size& image2size)
{
    vector<KeyPoint> keyPoint1to2;
    warpPoint(homographyMatrix, keypoints1, keyPoint1to2);


    return 0.1;
}

void VisionManager::drawOnImage(Image &image, const vector<KeyPoint> &points, Scalar color, int scale, int thickness)
{
    // for all keypoints
    for (unsigned int idx=0; idx<points.size(); ++idx)
    {

        // draw a cross at each keypoint location
        cv::putText(image, "x", points[idx].pt, FONT_HERSHEY_PLAIN, scale, color, thickness);
    }
}

