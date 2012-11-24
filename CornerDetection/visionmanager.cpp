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
typedef unsigned int uint;

using namespace cv;
using namespace std;

VisionManager::VisionManager()
{}

vector<double> VisionManager::inspectImagesWithHomography(const string &im1Filepath, const string &im2Filepath,
                                               const string &h1to2FilePath)
{
    Image im1 = imread(im1Filepath);
    Image im2 = imread(im2Filepath);
    Mat homographyMatrix(3,3,CV_64F);
    ifstream dataFile(h1to2FilePath.c_str());
    for (uint idxRow=0; idxRow<3; ++idxRow)
    {
        for (uint idxCol=0; idxCol<3; ++idxCol)
        {
            double val;
            dataFile >> val;
            homographyMatrix.at<double>(idxRow, idxCol) = val;
        }
    }
    return inspectImagesWithHomography(im1, im2, homographyMatrix);
}

vector<double> VisionManager::inspectImagesWithHomography(Mat im1, Mat im2, Mat h1to2)
{
    Image imMask1, imMask2;
    uint nCols = im1.cols,
         nRows = im1.rows;

    imMask1 = Image(nRows, nCols, CV_8UC1, Scalar(255));
    // Get all points from im1 that exists in im2 domain
    warpPerspective(imMask1, imMask2, h1to2, Size(nCols,nRows));
    // Get points from im2 that still exists in im1 domain
    warpPerspective(imMask2, imMask1, h1to2.inv(), Size(nCols,nRows));

    vector<KeyPoint> keyPoints1, keyPoints2;

    keyPoints1=this->inspect(im1, imMask1, fdtHarris),
    keyPoints2=this->inspect(im2, imMask2, fdtHarris);
    double repeatabilityHarris = measureRepeatability(keyPoints1, keyPoints2, h1to2, imMask1.size());

    keyPoints1=this->inspect(im1, imMask1, fdtStar);
    keyPoints2=this->inspect(im2, imMask2, fdtStar);
    double repeatabilityStar = measureRepeatability(keyPoints1, keyPoints2, h1to2, imMask1.size());

    cout << string("\nHarris Repeatability: ") << repeatabilityHarris << string("\nStar Repeatability: ") << repeatabilityStar;
    vector<double> repeatability;
    repeatability.insert(repeatability.end(), repeatabilityHarris);
    repeatability.insert(repeatability.end(), repeatabilityStar);
    return repeatability;
}


void VisionManager::warpPoint(Mat M, const Point2f& src, Point2f& dst)
{
    Mat srcM(3/* rows */,1 /* cols */,CV_64F);

    srcM.at<double>(0,0)=src.x;
    srcM.at<double>(1,0)=src.y;
    srcM.at<double>(2,0)=1.0;

    Mat dstM = M*srcM; //USE MATRIX ALGEBRA
    dst = Point2f((float)(dstM.at<double>(0,0)/dstM.at<double>(2,0)),(float)(dstM.at<double>(1,0)/dstM.at<double>(2,0)));
}

void VisionManager::warpPoint(Mat H, const vector<KeyPoint> &src, vector<KeyPoint> &dst)
{
    dst.clear();
    for (uint idx=0; idx<src.size(); ++idx)
    {
        KeyPoint srcKeyPoint = src[idx];
        Point2f dstPoint;
        warpPoint(H, srcKeyPoint.pt, dstPoint);
        dst.insert(dst.end(), KeyPoint(dstPoint, srcKeyPoint.size, srcKeyPoint.angle, srcKeyPoint.response, srcKeyPoint.octave, srcKeyPoint.class_id));
    }
}

double VisionManager::measureRepeatability(const vector<KeyPoint>& keypoints1, const vector<KeyPoint>& keypoints2, const Mat& homography1to2, const Size& image2size)
{
    Image im1to2(image2size, CV_8U, Scalar(0) );
    vector<KeyPoint> keypoints1to2;
    warpPoint(homography1to2, keypoints1, keypoints1to2);
    drawSquareOnImage(im1to2, keypoints1to2, 255);
    Image im2(image2size, CV_8U, Scalar(0));
    drawSquareOnImage(im2, keypoints2, 255);
    // Intersect images
    Image imInt;
    bitwise_and(im1to2,im2, imInt);
//        imshow("a", im1to2);
//        imshow("b", im2);
//        imshow("c", imInt);
//        waitKey();
    Contours contInt, cont1, cont2;
    // Find intersection contours
    findContours( imInt, contInt, CV_RETR_EXTERNAL , CV_CHAIN_APPROX_SIMPLE );
    // Find im1to2 contours (due to length AND keypoints' precision, # of keypoints may be less than designated)
    findContours( im1to2, cont1, CV_RETR_EXTERNAL , CV_CHAIN_APPROX_SIMPLE );
    findContours( im2, cont2, CV_RETR_EXTERNAL , CV_CHAIN_APPROX_SIMPLE );
    double nRepeated = 2 * contInt.size();
    double nTotal = cont1.size()+cont2.size();
    return nRepeated/nTotal;
}

void VisionManager::drawXOnImage(Image &image, const vector<KeyPoint> &points, Scalar color, int scale, int thickness)
{
    // for all keypoints
    for (uint idx=0; idx<points.size(); ++idx)
    {

        // draw a cross at each keypoint location
        putText(image, "x", points[idx].pt, FONT_HERSHEY_PLAIN, scale, color, thickness);
    }
}

void VisionManager::drawSquareOnImage(Mat &image, const vector<KeyPoint> &points, Scalar color, float length)
{
    for (uint idx=0; idx<points.size(); ++idx)
    {
        Point2f point = points[idx].pt;
        Point2f border1(point.x-length,point.y-length), border2(point.x+length,point.y+length);
        // draw a square at each keypoint location
        rectangle(image, border1, border2, color, CV_FILLED);
    }
}


vector<KeyPoint> VisionManager::inspect(Mat im, Mat mask, FeatureDetectorType fdt)
{
    vector<KeyPoint> keyPoints;
    if(fdt == fdtSift)
    {
        Ptr<FeatureDetector> fd = FeatureDetector::create("SIFT");
        fd->detect(im, keyPoints, mask);
    }
    else if (fdt == fdtStar)
    {
        Ptr<FeatureDetector> fd = FeatureDetector::create("STAR");
        fd->detect(im, keyPoints, mask);
    }
    else if (fdt == fdtBrief)
    {
        Ptr<FeatureDetector> fd = FeatureDetector::create("BRIEF");
        fd->detect(im, keyPoints, mask);
    }
    else if (fdt == fdtHarris)
    {
        HarrisCornerDetector hcd;
        hcd.detect(im, keyPoints, mask);
    }
    return keyPoints;
}
