#ifndef VISIONMANAGER_H
#define VISIONMANAGER_H
#include "harriscornerdetector.h"

class VisionManager
{
public:
    VisionManager();
    void inspectImageWithHomography(const std::string& imageFilepath, const std::string &homographyFilepath);
    void inspectImageWithHomography(cv::Mat imSrc, cv::Mat homographyMatrix);
    void warpPoint(cv::Mat H, const cv::Point2f& src, cv::Point2f& dst);
    void warpPoint(cv::Mat H, std::vector<cv::KeyPoint> &src, std::vector<cv::KeyPoint> &dst);
    double measureRepeatability(const std::vector<cv::KeyPoint>& keypoints1, const std::vector<cv::KeyPoint>& keypoints2, const cv::Mat& homography1to2, const cv::Size& image2size);
    void drawOnImage(cv::Mat &image, const std::vector<cv::KeyPoint> &points, cv::Scalar color= cv::Scalar(255,255,0), int scale=1, int thickness=1);

private:
    cv::Mat parseHomographyFile(std::string& homographyFilepath);

    std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
    std::vector<std::string> split(const std::string &s, char delim);
//    cv::Mat matrixStringToDouble (std::vector<std::vector<std::string> > matrixString);
};


#endif // VISIONMANAGER_H
