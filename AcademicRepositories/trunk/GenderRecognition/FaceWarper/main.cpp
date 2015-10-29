#include <QApplication>
#include "extractlandmarks.h"
#include "opencv2/opencv.hpp"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    cv::Mat imFrom = cv::imread(argv[1]);
    cv::Mat lmFrom = ExtractLandmarks::extractLandmarks(imFrom);
    cv::Mat imTo = cv::imread(argv[2]);
    cv::Mat lmTo = ExtractLandmarks::extractLandmarks(imTo);
    cv::Mat H = ExtractLandmarks::calculateHomography(lmFrom, lmTo);
    std::cout << H;

    cv::Mat imFromWarpedToTo,imToWarpedToFrom;
    cv::warpPerspective(imFrom, imFromWarpedToTo, H, imFrom.size(),cv::INTER_NEAREST);
    cv::warpPerspective(imTo, imToWarpedToFrom, H, imFrom.size(),cv::INTER_NEAREST);

    cv::imwrite("d:/test1.jpg",imFromWarpedToTo);
    cv::imwrite("d:/test2.jpg",imToWarpedToFrom);

    return 5;
}
