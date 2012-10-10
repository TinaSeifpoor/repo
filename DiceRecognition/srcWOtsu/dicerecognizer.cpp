#include "dicerecognizer.h"

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


    // Extract dice body contours(b)
    // Note: It is very hard to extract body contours of black dices due to similarity with background
    // therefore they'll be handled later on.
    Contour diceBodyContours = this->extractDiceBody(imGray);
    // Extract dice body contours(e)

    // Extract dice circles from bodies (b)
    ContourList diceCirclePerDice = this->extractDiceCirclesFromBody(diceBodyContours, imGray);
    //    ca->showContours(diceBodyContours, ca->assignRandomHierarchy(diceBodyContours), imGray.size());
    //    a();

    // Extract dice circles from bodies (e)
    // Extract remaining dice circles (b)
    // From black dices!
    Mat imBin = imGray > 150;
    Contour edgeContours;
    findContours(imBin, edgeContours, CV_RETR_EXTERNAL , CV_CHAIN_APPROX_SIMPLE );
    Contour diceCircles = this->pickDiceCircles(edgeContours);

    // Assumption: No two black dice will get too close to each other. Therefore we can group
    // dice circles if they are close to each other.
    ContourList diceCircleGrouped = this->groupDiceCircles(diceCircles, diceBodyContours, imGray);
    // Extract remaining dice circles (e)

    // Concat dice circle groups into dice circles per dice array (result array)
    int     nDiceCirclePerDice = diceCirclePerDice.size(),
            nDiceCircleGrouped = diceCircleGrouped.size(),
            nDiceCirclePerDiceFinal = nDiceCirclePerDice + nDiceCircleGrouped;
    diceCirclePerDice.resize(nDiceCirclePerDiceFinal);
    for (int i=nDiceCirclePerDice; i < nDiceCirclePerDiceFinal; ++i)
    {
        diceCirclePerDice[i] = diceCircleGrouped[i-nDiceCirclePerDice];
    }


    multiset<int> numbers;
    multiset<int>::iterator itNumbers = numbers.begin();
    foreach (Contour diceCircleContour, diceCirclePerDice)
    {
        itNumbers = numbers.insert(itNumbers, diceCircleContour.size());
    }
    Mat imResult;
    cvtColor(imGray, imResult, CV_GRAY2RGB);

//    showResults(diceCircleContours, imResult);
//    imshow ("result", imResult);
//    waitKey();

    return numbers;
}

Mat DiceRecognizer::autoThreshold(Mat imGray, bool isBright, int sigma)
{
    Mat imTh;
    Scalar imMeanGray, imStdDevGray;
    meanStdDev(imGray, imMeanGray, imStdDevGray);
    Scalar thresholds;
    thresholds[0] = imMeanGray[0] + imStdDevGray[0] * sigma;
    thresholds[1] = 255;
    if (!isBright)
    {
        cv::threshold(255-imGray, imTh, thresholds[0], thresholds[1], CV_8U);
    }
    else
    {
        cv::threshold(imGray, imTh, thresholds[0], thresholds[1], CV_8U);
    }
    return imTh;
}

Mat DiceRecognizer::morphSquare (Mat imGray, int morphType, double length)
{
    Mat element = getStructuringElement(MORPH_ELLIPSE, Size(length*2+1, length*2+1), Point(length, length));
    Mat imMorphed;
    //    dilate(imGray, imMorphed, element, Point(0,0), 3);
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
        ca->drawContours_xld(resultContours[i], ca->assignRandomHierarchy(resultContours[i]), imGray, color);
        string text = rawText.arg(i).arg(diceNumber).toAscii().constData();
        putText(imGray, text, Point(20,i*20+100), FONT_HERSHEY_PLAIN, 1.5, color, 1, CV_AA);
    }
}

Contour DiceRecognizer::pickDiceBody(Contour diceBodyCandidates)
{
    int diceBodyMinAreaThreshold=350, diceBodyMaxAreaThreshold=2000;
    double diceBodyMinAreaRectangularity=.5, diceBodyMaxAreaRectangularity=1;
    Contour diceBodyContour, tempContours;
    ca->selectContoursByArea(diceBodyCandidates,
                             diceBodyMinAreaThreshold, diceBodyMaxAreaThreshold,
                             &tempContours);
    ca->selectContoursByRectangularity(tempContours,
                                       diceBodyMinAreaRectangularity, diceBodyMaxAreaRectangularity,
                                       &diceBodyContour);
    return diceBodyContour;
}

Contour DiceRecognizer::pickDiceCircles(Contour diceCircleCandidates)
{
    int diceCircleMinAreaThreshold=10, diceCircleMaxAreaThreshold=100;
    double diceCircleMinCircularity=.2, diceCircleMaxCircularity = 1;
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
    ContourList diceCircleGrouped;
    ContourList::iterator itDiceCircleGrouped = diceCircleGrouped.begin();
    int nDiceBodies = diceBodyContours.size();
    for (int i=0; i<nDiceBodies; ++i)
    {
        Contour diceBodyContour;
        ca->selectContours(diceBodyContours, i, &diceBodyContour);
        //        ca->showContours(diceBodyContour, ca->assignRandomHierarchy(diceBodyContour), im.size());
        //        waitKey();
        Contour diceCircles = this->extractDiceCircle(diceBodyContour, im, isBright);
//                ca->showContours(diceCircles, ca->assignRandomHierarchy(diceCircles), im.size());
//                waitKey();
        itDiceCircleGrouped = diceCircleGrouped.insert(itDiceCircleGrouped,diceCircles);
    }
    return diceCircleGrouped;
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
//    imshow("a", imBin);
//    waitKey();
    Contour edgeContours;
    findContours(imBin, edgeContours, CV_RETR_EXTERNAL , CV_CHAIN_APPROX_SIMPLE );
    return this->pickDiceCircles(edgeContours);
}

Contour DiceRecognizer::extractDiceBody(Mat im)
{
    Contour edgeContours;
    Mat imCanny, imClean = this->cleanDiceImage(im);
    Canny(imClean, imCanny, 5, 40, 5);
//    imshow ("a", imClean);
    findContours( imCanny, edgeContours, CV_RETR_EXTERNAL , CV_CHAIN_APPROX_SIMPLE );
//    ca->showContours(edgeContours,ca->assignRandomHierarchy(edgeContours), im.size());
//    waitKey();
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
//    imshow ("before threshold", imGray);
//    waitKey();
    int histSize = 256;
    float range[] = {0, 256};
    const float* histRange = {range};
    vector<int> histData;
    histData.resize(256);
    for (int i=0; i < imGray.cols; ++i)
        for (int j=0; j < imGray.rows; ++j)
            int intensity = imGray[i][j];
    calcHist(&imGray, 1, 0, Mat(), histData, 1, &histSize, &histRange);
    //
    int total = imGray.rows * imGray.cols;

    float sum = 0;
    for (int t=0; t<256; ++t)
        sum += t * histData[t];
    float sumB = 0;
    int wB = 0, wF = 0;

    float varMax = 0;
    int threshold = 0;

    for (int t=0; t<256; ++t)
    {
        wB += histData[t]; // Weight Background
        if (wB==0)
            continue;
        wF = total - wB; // Weight Foreground
        if (wF == 0)
            break;
        sumB += (float) (t * histData[t]);

        float mB = sumB / wB; // Mean Background
        float mF = (sum - sumB) / wF; // Mean Foreground

        // Calculate Between Class Variance
        float varBetween = (float)wB * (float)wF * (mB - mF) * (mB - mF);

        // Check if new maximum found
        if (varBetween > varMax)
        {
            varMax = varBetween;
            threshold = t;
        }
    }
    Mat imClean = imGray > threshold;
    imshow ("after threshold", imClean);
    imshow ("before threshold", imGray);
    waitKey();
//    blur(imGray, imMean, Size(199,199));
//    Mat imDiff = imGray - imMean;
//    Mat imMask = imDiff > 120;
//    Mat imClean;
//    bitwise_and (imGray, imMask, imClean);
    return imClean;
}

DiceRecognizer::DiceRecognizer()
{
    this->ca = new ContourAnalysis();
}
