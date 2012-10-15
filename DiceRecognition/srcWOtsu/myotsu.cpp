#include "myotsu.h"
using namespace cv;
using namespace std;
static const double pi = 3.14159265358979323846;

MyOtsu::MyOtsu()
{
}

Mat MyOtsu::calcMyOtsu(Mat imGray)
{
    Mat imOtsuMine;
    int histSize = 256;
    float range[] = {0, 256};
    const float* histRange = {range};
    Mat histData;
    calcHist(&imGray, 1, 0, Mat(), histData, 1, &histSize, &histRange);
    int th;
    float minVar = -1;
    for (int thCand=0; thCand<histSize; ++thCand)
    {
        float classVar = this->calcClassVariance(histData, thCand);
        if (classVar>minVar)
        {
            minVar = classVar;
            th = thCand;
        }
    }
    imOtsuMine = imGray>=th;
    return imOtsuMine;
}

Mat MyOtsu::calcCVOtsu(Mat imGray)
{
    Mat imOtsuCv;
    threshold (imGray, imOtsuCv, 0, 255, THRESH_BINARY|THRESH_OTSU);
    return imOtsuCv;
}

float MyOtsu::calcClassVariance(Mat hist, int th)
{
    float darkMean=0, brightMean=0;
    float nDarkPixels=0, nBrightPixels=0;
    for(int i = 0; i < 255; ++i)
    {
        float binVal = hist.at<float>(i, 0);
        if (i<=th)
        {
            // background
            nDarkPixels+=binVal;
            darkMean+=binVal*i;
        }
        else
        {
            // foreground
            nBrightPixels+=binVal;
            brightMean+=binVal*i;
        }
    }
    if (!nDarkPixels || !nBrightPixels)
        return -1;
    darkMean/=nDarkPixels;
    brightMean/=nBrightPixels;
    float nPixels = nDarkPixels+nBrightPixels;
    float darkWeight = nDarkPixels/nPixels;
    float brightWeight = nBrightPixels/nPixels;
    return darkWeight*brightWeight*pow(darkMean-brightMean,2);
}
