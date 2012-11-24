#include "visionmanager.h"
#include <iostream>
#include <fstream>
#include "math.h"
#include "stdio.h"
#include <sstream>
#include <vector>
#include "stdlib.h"

typedef cv::Mat Image;
typedef std::vector<cv::Point> ContourPoints;
typedef std::vector<ContourPoints> Contours;

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
    Image imMaskSrc, imMaskDst, imDst;
    int nCols = imSrc.cols,
        nRows = imSrc.rows;

    imMaskSrc = Image(nRows, nCols, CV_8UC1, Scalar(255));
    warpPerspective(imMaskSrc, imMaskDst, homographyMatrix, Size(nCols,nRows));
    warpPerspective(imMaskDst, imMaskSrc, homographyMatrix.inv(), Size(nCols,nRows));

    warpPerspective(imSrc, imDst, homographyMatrix, Size(nCols,nRows));

    vector<KeyPoint> keyPointsSrc=this->inspectWithHarris(imSrc, imMaskSrc),
                     keyPointsDst=this->inspectWithHarris(imDst, imMaskDst);
    double repeatability = measureRepeatability(keyPointsSrc, keyPointsDst, homographyMatrix, imDst.size());
    cout << repeatability;
    //
    Image imSrcDisp, imDstDisp, imSrc2DstDisp;
    imSrc.copyTo(imSrcDisp);
    imDst.copyTo(imDstDisp);
    imDst.copyTo(imSrc2DstDisp);
    drawXOnImage(imSrcDisp, keyPointsSrc);
    drawXOnImage(imDstDisp, keyPointsDst);
    vector<KeyPoint> keyPointsSrc2Dst;
    warpPoint(homographyMatrix, keyPointsSrc, keyPointsSrc2Dst);
    drawXOnImage(imSrc2DstDisp, keyPointsSrc2Dst);
    imshow("Src", imSrcDisp);
    imshow("Dst", imDstDisp);
    imshow("maskDst", imMaskDst);
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
    dst = Point2f((float)(dstM.at<double>(0,0)/dstM.at<double>(2,0)),(float)(dstM.at<double>(1,0)/dstM.at<double>(2,0)));
}

void VisionManager::warpPoint(Mat H, const vector<KeyPoint> &src, vector<KeyPoint> &dst)
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
    float length = 1.5;
    Image im1to2(image2size, CV_8U, Scalar(0) );
    vector<KeyPoint> keypoints1to2;
    warpPoint(homography1to2, keypoints1, keypoints1to2);
    drawSquareOnImage(im1to2, keypoints1to2, 255, length);
    Image im2(image2size, CV_8U, Scalar(0) );
    drawSquareOnImage(im2, keypoints2, 255, length);
    // Intersect images
    Image imInt;
    bitwise_and(im1to2,im2, imInt);
//    imshow("a", im1to2);
//    imshow("b", im2);
//    imshow("c", imInt);
//    waitKey();
    Contours contInt;
    findContours( imInt, contInt, CV_RETR_EXTERNAL , CV_CHAIN_APPROX_SIMPLE );
    double nRepeated = 2 * contInt.size();
    double nTotal = keypoints1.size()+keypoints2.size();
    return nRepeated/nTotal;
}

void VisionManager::drawXOnImage(Image &image, const vector<KeyPoint> &points, Scalar color, int scale, int thickness)
{
    // for all keypoints
    for (unsigned int idx=0; idx<points.size(); ++idx)
    {

        // draw a cross at each keypoint location
        putText(image, "x", points[idx].pt, FONT_HERSHEY_PLAIN, scale, color, thickness);
    }
}

void VisionManager::drawSquareOnImage(Mat &image, const vector<KeyPoint> &points, Scalar color, float length)
{
    for (unsigned int idx=0; idx<points.size(); ++idx)
    {
        Point2f point = points[idx].pt;
        Point2f border1(point.x-length,point.y-length), border2(point.x+length,point.y+length);
        // draw a square at each keypoint location
        rectangle(image, border1, border2, color, CV_FILLED);
    }
}



vector<KeyPoint> VisionManager::inspectWithHarris(Mat im, Mat mask)
{
    vector<KeyPoint> keyPoints;
    HarrisCornerDetector fd;
    fd.detect(im, keyPoints, mask);
    return keyPoints;
}

vector<KeyPoint> VisionManager::inspectWithSift(Mat im, Mat mask)
{
    vector<KeyPoint> keyPoints;
    Ptr<FeatureDetector> fd = FeatureDetector::create("STAR");
    fd->detect(im, keyPoints);
//    delete fd;
    return keyPoints;
}

