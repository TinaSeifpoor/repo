#ifndef EXTRACTLANDMARKS_H
#define EXTRACTLANDMARKS_H

namespace cv{
class Mat;
template <typename> class Rect_;
typedef Rect_<int> Rect;
template <typename> class Size_;
typedef Size_<int> Size;
}

class FaceLandmarks
{
public:
    static cv::Mat extractLandmarks(cv::Mat frame, bool *isSuccessful=0);
    static cv::Mat extractLandmarks(cv::Mat frame, cv::Rect frameRect, bool *isSuccessful=0);
    static cv::Mat extractFaceAndLandmarks(cv::Mat frame, cv::Mat& face);
    static float calculateHomography(cv::Mat fromPoints, cv::Mat toPoints, cv::Mat& homography);

    static cv::Mat alignImage(cv::Mat frame, cv::Mat goldenLandmarks);
//    static cv::Mat calculateOPA(cv::Mat fromPoints, cv::Mat toPoints);
};

#endif // EXTRACTLANDMARKS_H
