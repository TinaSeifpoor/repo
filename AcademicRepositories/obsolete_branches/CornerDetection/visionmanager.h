#ifndef VISIONMANAGER_H
#define VISIONMANAGER_H
#include "harriscornerdetector.h"

class VisionManager
{
    // All definitions
    typedef cv::Mat Image;
    typedef std::vector<cv::Point> ContourPoints;
    typedef std::vector<ContourPoints> Contours;
    typedef unsigned int uint;
    typedef cv::Mat Homography;
    typedef std::vector<cv::KeyPoint> KeyPoints;
    typedef double Repeatability;
    typedef std::vector<Repeatability> RepeatabilityList;
    typedef cv::Size Size;
    typedef cv::Point2f Point2f;
    typedef cv::Scalar Scalar;
    typedef cv::Mat Mat;
    typedef cv::KeyPoint KeyPoint;
    // All definitions

public:
    enum FeatureDetectorType
    {
        fdtHarris = 0,
        fdtSift = 1,
        fdtStar = 2,
        fdtBrief = 3
    };

    VisionManager(){}
    Repeatability testFeatureDetectorRepeatability(Image im1, Image im2, Image h1to2, VisionManager::FeatureDetectorType fdt);
    void warpPoint(const Homography H, const Point2f &src, Point2f &dst);
    void warpPoint(const Homography H, const KeyPoints &src, KeyPoints &dst);
    Repeatability measureRepeatability(const KeyPoints& keypoints1, const KeyPoints& keypoints2, const Homography& homography1to2, const Size& image2size);




private:
    KeyPoints inspect(Image im, Image mask, FeatureDetectorType fdt);

    // Group key points
    void drawSquareOnImage(Image &image, const KeyPoints &points, Scalar color= Scalar(255), float length=1);
    //
    // Display key points
    void drawXOnImage(Image &image, const KeyPoints &points, Scalar color= Scalar(255,255,0), int scale=1, int thickness=1);
};


#endif // VISIONMANAGER_H
