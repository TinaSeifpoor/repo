#include "RandomDiceRecognizer.h"

#include <opencv2\opencv.hpp>

using std::multiset;

multiset<int> RandomDiceRecognizer::readNumbers(const cv::Mat& img)
{
    cv::imshow("x", img);

    multiset<int> numbers;
    
    int diceCount = rand() % 3 + 1;
    for (int i=0; i<diceCount; i++)
        numbers.insert(rand() % 6 + 1);

    //    Mat imHist;
    //    /// Establish the number of bins
    //    int histSize = 256;

    //    /// Set the ranges ( for B,G,R) )
    //    float range[] = { 0, 256 } ;
    //    const float* histRange = { range };

    //    bool uniform = true; bool accumulate = false;
    //    calcHist( &img, 1, 0, Mat(), imHist, 1, &histSize, &histRange, uniform, accumulate );

    cv::imshow("x", img);
    cv::waitKey(20);

    return numbers;
}
