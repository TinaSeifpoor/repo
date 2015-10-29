#ifndef EXTRACTLANDMARKS_H
#define EXTRACTLANDMARKS_H

namespace cv{
class Mat;
}

class ExtractLandmarks
{
public:
    static cv::Mat extractLandmarks(cv::Mat frame, bool *isSuccessful=0);
    static cv::Mat calculateHomography(cv::Mat fromPoints, cv::Mat toPoints);
    static cv::Mat calculateOPA(cv::Mat fromPoints, cv::Mat toPoints);
    static cv::Mat normalizePoints(cv::Mat points);
    static cv::Mat alignLandmarks(cv::Mat from, cv::Mat to);
};

#endif // EXTRACTLANDMARKS_H
