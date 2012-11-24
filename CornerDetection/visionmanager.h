#ifndef VISIONMANAGER_H
#define VISIONMANAGER_H
#include "harriscornerdetector.h"

class VisionManager
{
public:
    VisionManager();
    void inspectImageWithHomography(const std::string& imageFilepath, const std::string &homographyFilepath);
    void inspectImageWithHomography(cv::Mat imSrc, cv::Mat homographyMatrix);
    void warpPoint(const cv::Mat H, const cv::Point2f& src, cv::Point2f& dst);
    void warpPoint(const cv::Mat H, const std::vector<cv::KeyPoint> &src, std::vector<cv::KeyPoint> &dst);
    double measureRepeatability(const std::vector<cv::KeyPoint>& keypoints1, const std::vector<cv::KeyPoint>& keypoints2, const cv::Mat& homography1to2, const cv::Size& image2size);

private:
    cv::Mat parseHomographyFile(std::string& homographyFilepath);
    std::vector<cv::KeyPoint> inspectWithHarris(cv::Mat im, cv::Mat mask);
    std::vector<cv::KeyPoint> inspectWithSift(cv::Mat im, cv::Mat mask);
    std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
    std::vector<std::string> split(const std::string &s, char delim);
//    cv::Mat matrixStringToDouble (std::vector<std::vector<std::string> > matrixString);

    void drawXOnImage(cv::Mat &image, const std::vector<cv::KeyPoint> &points, cv::Scalar color= cv::Scalar(255,255,0), int scale=1, int thickness=1);
    void drawSquareOnImage(cv::Mat &image, const std::vector<cv::KeyPoint> &points, cv::Scalar color= cv::Scalar(255), float length=1.5);
};


#endif // VISIONMANAGER_H
