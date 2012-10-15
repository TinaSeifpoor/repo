#include "dicerecognizer.h"
#include "myotsu.h"
using std::multiset;

using namespace cv;
#include <QString>

std::multiset<int> DiceRecognizer::readNumbers(const cv::Mat &im)
{
    int nChannels = im.channels();
    Mat imGray;

    if (nChannels > 1)
        cvtColor(im, imGray, CV_RGB2GRAY);
    else
        imGray.setTo(im);

    // Otsu part (b)
//    MyOtsu mo;
//    Mat imMyOtsu = mo.calcMyOtsu(imGray);
//    Mat imCVOtsu = mo.calcCVOtsu(imGray);
//    Mat imDiffOtsu = (imMyOtsu+1-imCVOtsu)>0;
//    imshow("my otsu vs. cv otsu", imDiffOtsu);
//    waitKey();
    // Otsu part (e)


    // Extract dice body contours(b)
    // Note: It is very hard to extract body contours of black dice due to similarity with background
    // therefore they'll be handled later on.
    Contour diceBodyContours = this->extractDiceBody(imGray);
    // Extract dice body contours(e)

    // Extract dice circles from bodies (b)
    ContourList circlesPerDice = this->extractDiceCirclesFromBody(diceBodyContours, imGray);

    // Extract dice circles from bodies (e)
    // Extract remaining dice circles (b)
    // From black dice!
    Mat imBin = imGray > 150;
    Contour edgeContours;
    findContours(imBin, edgeContours, CV_RETR_EXTERNAL , CV_CHAIN_APPROX_SIMPLE );
    Contour diceCircles = this->pickDiceCircles(edgeContours);

    // Assumption: No two black dice will get too close to each other. Therefore we can group
    // dice circles if they are close to each other.
    ContourList diceCircleGrouped = this->groupDiceCircles(diceCircles, diceBodyContours, imGray);
    // Extract remaining dice circles (e)

    // Concat dice circle groups into dice circles per dice array (result array)
    int     nCirclesPerDice = circlesPerDice.size(),
            nCirclesGrouped = diceCircleGrouped.size(),
            nCirclesPerDiceFinal = nCirclesPerDice + nCirclesGrouped;
    circlesPerDice.resize(nCirclesPerDiceFinal);
    for (int i=nCirclesPerDice; i < nCirclesPerDiceFinal; ++i)
    {
        circlesPerDice[i] = diceCircleGrouped[i-nCirclesPerDice];
    }


    multiset<int> numbers;
    multiset<int>::iterator itNumbers = numbers.begin();
    foreach (Contour diceCircleContour, circlesPerDice)
    {
        itNumbers = numbers.insert(itNumbers, diceCircleContour.size());
    }

//    Mat imResult;
//    cvtColor(imGray, imResult, CV_GRAY2RGB);
//    showResults(circlesPerDice, imResult);
//    imshow ("result", imResult);
//    waitKey();

    return numbers;
}


Mat DiceRecognizer::morphSquare (Mat imGray, int morphType, double length)
{
    Mat element = getStructuringElement(MORPH_ELLIPSE, Size(length*2+1, length*2+1), Point(length, length));
    Mat imMorphed;
    morphologyEx(imGray, imMorphed, morphType, element, Point(-1, -1), 3);
    return imMorphed;
}

void DiceRecognizer::showResults(ContourList resultContours, Mat imGray)
{
    QString rawText(QString("Dice %1: %2"));
    for (int i=0; i<resultContours.size(); ++i)
    {
        int diceNumber = resultContours[i].size();
        Scalar color((rand()&255), (rand()&255), (rand()&255) );
        ca->drawContours_xld(resultContours[i], imGray, color);
        string text = rawText.arg(i).arg(diceNumber).toAscii().constData();
        putText(imGray, text, Point(20,i*20+100), FONT_HERSHEY_PLAIN, 1.5, color, 1, CV_AA);
    }
}

Contour DiceRecognizer::pickDiceBody(Contour diceBodyCandidates)
{
    int diceBodyMinAreaThreshold=350, diceBodyMaxAreaThreshold=2000;
    double diceBodyMinRectangularity=.5, diceBodyMaxRectangularity=1;
    Contour diceBodyContour, tempContours;
    ca->selectContoursByArea(diceBodyCandidates,
                             diceBodyMinAreaThreshold, diceBodyMaxAreaThreshold,
                             &tempContours);
    ca->selectContoursByRectangularity(tempContours,
                                       diceBodyMinRectangularity, diceBodyMaxRectangularity,
                                       &diceBodyContour);
    return diceBodyContour;
}

Contour DiceRecognizer::pickDiceCircles(Contour diceCircleCandidates)
{
    int diceCircleMinAreaThreshold=10, diceCircleMaxAreaThreshold=100;
    double diceCircleMinCircularity=.4, diceCircleMaxCircularity = 1;
    Contour diceCircleContour, tempContours;
    ca->selectContoursByArea(diceCircleCandidates,
                             diceCircleMinAreaThreshold, diceCircleMaxAreaThreshold,
                             &tempContours);
    ca->selectContoursByCircularity(tempContours,
                                    diceCircleMinCircularity, diceCircleMaxCircularity,
                                    &diceCircleContour);

    return diceCircleContour;
}

ContourList DiceRecognizer::extractDiceCirclesFromBody(Contour diceBodyContours, Mat im, bool isBright)
{
    ContourList diceCirclesGrouped;
    ContourList::iterator itDiceCirclesGrouped = diceCirclesGrouped.begin();
    int nDicebodies = diceBodyContours.size();
    for (int i=0; i<nDicebodies; ++i)
    {
        Contour diceBodyContour;
        ca->selectContours(diceBodyContours, i, &diceBodyContour);
        Contour diceCircles = this->extractDiceCircle(diceBodyContour, im, isBright);
        itDiceCirclesGrouped = diceCirclesGrouped.insert(itDiceCirclesGrouped,diceCircles);
    }
    return diceCirclesGrouped;
}

Contour DiceRecognizer::extractDiceCircle(Contour diceBody, Mat im, bool isBright)
{

    Mat imMaskDiceBody = Mat::zeros(im.size(), im.type());
    drawContours(imMaskDiceBody, diceBody, -1, Scalar(255), CV_FILLED);
    Mat imGrayDiceBody(im.size(), CV_8U);
    Mat imBin;
    if (isBright)
    {
        imGrayDiceBody.setTo(Scalar(255));
        im.copyTo(imGrayDiceBody, imMaskDiceBody);
        imBin = imGrayDiceBody < 150;
    }
    else
    {
        imGrayDiceBody.setTo(Scalar(0));
        im.copyTo(imGrayDiceBody, imMaskDiceBody);
        imBin = imGrayDiceBody > 150;
    }
    Contour edgeContours;
    findContours(imBin, edgeContours, CV_RETR_EXTERNAL , CV_CHAIN_APPROX_SIMPLE );
    return this->pickDiceCircles(edgeContours);
}

Contour DiceRecognizer::extractDiceBody(Mat im)
{
    Contour edgeContours;
    Mat imCanny, imClean = this->cleanDiceImage(im);
    Canny(imClean, imCanny, 5, 40, 5);
    findContours( imCanny, edgeContours, CV_RETR_EXTERNAL , CV_CHAIN_APPROX_SIMPLE );
    Contour convex( edgeContours.size() );
    for( int i = 0; i < edgeContours.size(); i++ )
    {  convexHull( Mat(edgeContours[i]), convex[i], false ); }
    return this->pickDiceBody(convex);
}

ContourList DiceRecognizer::groupDiceCircles(Contour diceCircle, Contour filter, Mat im)
{
    Mat imMask = Mat::zeros(im.size(), im.type());
    drawContours(imMask, diceCircle, -1, Scalar(255), CV_FILLED);
    drawContours(imMask, filter, -1, Scalar(0), CV_FILLED);
    Mat imDiceBody = this->morphSquare(imMask, MORPH_DILATE, 7);
    Contour diceBody;
    findContours( imDiceBody, diceBody, CV_RETR_EXTERNAL , CV_CHAIN_APPROX_SIMPLE );
    return this->extractDiceCirclesFromBody(diceBody, imMask, false);
}

Mat DiceRecognizer::cleanDiceImage(Mat imGray)
{
    Mat imMean;
    blur(imGray, imMean, Size(121,121));
    Mat imDiff = imGray - imMean;
    Mat imMask = imDiff > 120;
    Mat imClean;
    bitwise_and (imGray, imMask, imClean);
    return imClean;
}

DiceRecognizer::DiceRecognizer()
{
    this->ca = new ContourAnalysis();
}
