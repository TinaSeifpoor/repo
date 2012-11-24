#ifndef VISIONMANAGER_H
#define VISIONMANAGER_H
#include "harriscornerdetector.h"

class VisionManager
{
public:
    VisionManager();
    std::vector<double> inspectImagesWithHomography(const std::string& im1FilePath, const std::string& im2FilePath, const std::string &h1to2FilePath);
    std::vector<double> inspectImagesWithHomography(cv::Mat im1, cv::Mat im2, cv::Mat h1to2);
    void warpPoint(const cv::Mat H, const cv::Point2f& src, cv::Point2f& dst);
    void warpPoint(const cv::Mat H, const std::vector<cv::KeyPoint> &src, std::vector<cv::KeyPoint> &dst);
    double measureRepeatability(const std::vector<cv::KeyPoint>& keypoints1, const std::vector<cv::KeyPoint>& keypoints2, const cv::Mat& homography1to2, const cv::Size& image2size);


    enum FeatureDetectorType
    {
        fdtHarris = 0,
        fdtSift = 1,
        fdtStar = 2,
        fdtBrief = 3
    };

private:
    cv::Mat parseHomographyFile(std::string& homographyFilepath);

    std::vector<cv::KeyPoint> inspect(cv::Mat im, cv::Mat mask, FeatureDetectorType fdt);

    std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
    std::vector<std::string> split(const std::string &s, char delim);


    void drawXOnImage(cv::Mat &image, const std::vector<cv::KeyPoint> &points, cv::Scalar color= cv::Scalar(255,255,0), int scale=1, int thickness=1);
    void drawSquareOnImage(cv::Mat &image, const std::vector<cv::KeyPoint> &points, cv::Scalar color= cv::Scalar(255), float length=.5);
    //
};


#endif // VISIONMANAGER_H
