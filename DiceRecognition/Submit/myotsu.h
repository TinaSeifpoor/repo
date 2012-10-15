#ifndef MYOTSU_H
#define MYOTSU_H
#include <opencv2/opencv.hpp>

class MyOtsu
{
public:
    MyOtsu();
    cv::Mat calcMyOtsu (cv::Mat imGray);
    cv::Mat calcCVOtsu (cv::Mat imGray);
private:
    float calcClassVariance(cv::Mat hist, int th);
};

#endif // MYOTSU_H
