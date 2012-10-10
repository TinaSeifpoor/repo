#ifndef DICERECOGNIZER_H
#define DICERECOGNIZER_H

#include "IDiceRecongizer.h"
#include "contouranalysis.h"

class DiceRecognizer : public IDiceRecognizer
{
public:
    DiceRecognizer();
    std::multiset<int> readNumbers(const cv::Mat& img);
private:
    cv::Mat autoThreshold(cv::Mat imGray, bool isBright=true, int sigma=4);
    cv::Mat morphSquare (cv::Mat imGray, int morphType, double length);
    void showResults(ContourList resultContours, cv::Mat imGray);
    Contour pickDiceBody (Contour diceBodyCandidates);
    Contour pickDiceCircles (Contour diceCircleCandidates);
    ContourList extractDiceCirclesFromBody (Contour diceBodyContours, cv::Mat im, bool isBright=true);
    Contour extractDiceCircle (Contour diceBody, cv::Mat im, bool isBright=true);
    Contour extractDiceBody (cv::Mat im);
    ContourList groupDiceCircles (Contour diceCircle, Contour filter, cv::Mat im);
    cv::Mat cleanDiceImage (cv::Mat imGray);


    ContourAnalysis *ca;

//    cv::Mat dCircle (cv::Mat imGray, cv::Mat imErosion, int radius);
};

#endif // DICERECOGNIZER_H
