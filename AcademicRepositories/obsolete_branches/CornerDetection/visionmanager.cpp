#include "visionmanager.h"
#include <opencv2/nonfree/features2d.hpp>


VisionManager::Repeatability VisionManager::testFeatureDetectorRepeatability(Image im1, Image im2, Homography h1to2, VisionManager::FeatureDetectorType fdt)
{
    Image imMask1, imMask2;
    uint nCols = im1.cols,
         nRows = im1.rows;

    imMask1 = Image(nRows, nCols, CV_8UC1, Scalar(255));
    // Get all points from im1 that exists in im2 domain
    warpPerspective(imMask1, imMask2, h1to2, Size(nCols,nRows));
    // Get points from im2 that still exists in im1 domain
    warpPerspective(imMask2, imMask1, h1to2.inv(), Size(nCols,nRows));

    KeyPoints keyPoints1, keyPoints2;

    keyPoints1=this->inspect(im1, imMask1, fdt),
    keyPoints2=this->inspect(im2, imMask2, fdt);

    Repeatability repeatability = measureRepeatability(keyPoints1, keyPoints2, h1to2, imMask1.size());

    std::cout << "Repeatability : " << repeatability << " for method: " << fdt << std::endl;
    #ifdef Debug
    {
        imshow("Repeatability", im2);
        cv::waitKey();
    }
    #endif



    return repeatability;
}


void VisionManager::warpPoint(Homography H, const Point2f& src, Point2f& dst)
{
    cv::Mat srcM(3, 1, CV_64F);

    srcM.at<double>(0,0)=src.x;
    srcM.at<double>(1,0)=src.y;
    srcM.at<double>(2,0)=1.0;

    cv::Mat dstM = H*srcM;
    dst = Point2f((float)(dstM.at<double>(0,0)/dstM.at<double>(2,0)),(float)(dstM.at<double>(1,0)/dstM.at<double>(2,0)));
}

void VisionManager::warpPoint(Homography H, const KeyPoints &src, KeyPoints &dst)
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

VisionManager::Repeatability VisionManager::measureRepeatability(const KeyPoints& keypoints1, const KeyPoints& keypoints2, const Mat& homography1to2, const Size& image2size)
{
    KeyPoints keypoints1to2;
    warpPoint(homography1to2, keypoints1, keypoints1to2);


    Image im1to2(image2size, CV_8U, Scalar(0) );
    drawSquareOnImage(im1to2, keypoints1to2, 255);
    Image im2(image2size, CV_8U, Scalar(0));
    drawSquareOnImage(im2, keypoints2, 255);
    // Intersect images
    Image imInt;
    bitwise_and(im1to2,im2, imInt);

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

void VisionManager::drawXOnImage(Image &image, const KeyPoints &points, Scalar color, int scale, int thickness)
{
    // for all keypoints
    for (uint idx=0; idx<points.size(); ++idx)
    {

        // draw a cross at each keypoint location
        putText(image, "x", points[idx].pt, cv::FONT_HERSHEY_PLAIN, scale, color, thickness);
    }
}

void VisionManager::drawSquareOnImage(Mat &image, const KeyPoints &points, Scalar color, float length)
{
    for (uint idx=0; idx<points.size(); ++idx)
    {
        Point2f point = points[idx].pt;
        Point2f border1(point.x-length,point.y-length), border2(point.x+length,point.y+length);
        // draw a square at each keypoint location
        rectangle(image, border1, border2, color, CV_FILLED);
    }
}


VisionManager::KeyPoints VisionManager::inspect(Mat im, Mat mask, FeatureDetectorType fdt)
{
    using namespace cv;
    KeyPoints keyPoints;
    if(fdt == fdtSift)
    {
        SIFT fd;
        fd.detect(im, keyPoints, mask);
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
        HarrisCornerDetector fd;
        fd.detect(im, keyPoints, mask);
    }
    return keyPoints;
}
