#include "myharris.h"
typedef cv::Mat Image;
using std::string;
using namespace cv;
MyHarris::MyHarris(const string filePath)
{
    Image im = imread(filePath);
    imshow("asd",im);
    waitKey();
}
