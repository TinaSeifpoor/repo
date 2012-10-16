#include "leafrecognizer.h"

using namespace cv;
using namespace std;

LeafRecognizer::LeafRecognizer()
{
}

void LeafRecognizer::recognize(cv::Mat im)
{
    Mat imGray;
    if (im.channels()==3)
        cvtColor(im, imGray, CV_RGB2GRAY);
    else
        im.copyTo(imGray,im);
    Mat imTh, imCanny;
    imTh = this->binThreshold(imGray);
//    imTh = imGray < 240;
//    threshold (imGray, imTh, 0, 255, THRESH_BINARY|THRESH_OTSU);
    Contour leafExteriorContour, leafExteriorContourCandidates;
    findContours(imTh, leafExteriorContourCandidates, CV_RETR_EXTERNAL , CV_CHAIN_APPROX_SIMPLE);
    ContourAnalysis ca;
//    ca.selectContoursByRectangularity(leafExteriorContourCandidates, 0, 0.9, &leafExteriorContour);
    ca.selectContoursByArea(leafExteriorContourCandidates, 100000, 1000000, &leafExteriorContour);
    drawContours(im, leafExteriorContour, 0, Scalar(255,0,0), 5);
//    ca.showContours(leafExteriorContour, imGray.size());
    imshow("test", im);
    waitKey();
    int a = 5;
}

Mat LeafRecognizer::binThreshold(Mat im)
{
//    Mat imBinTh;
    int histSize = 256;
    float range[] = {0, 256};
    const float* histRange = {range};
    Mat histData;
    calcHist(&im, 1, 0, Mat(), histData, 1, &histSize, &histRange);
    return im<this->getBinThVal(histData);
}

float LeafRecognizer::getBinThVal(Mat hist)
{
    vector<float> pdf(256);
    float nPixels=0;
    for(int i = 0; i < 256; ++i)
    {
        float binVal = hist.at<float>(i, 0);
        pdf[i]=binVal;
        nPixels+=binVal;
    }
    vector<float> pdfMinima;
    float sigma = 1, size = 1;
//    if (pdfMinima.size()!=1)
//    {
//        size+=2;
//        if (pdfMinima.size()!=1)
//        {
            pdf[0] = 1;
            pdf[1] = 2;
            pdf[2] = 3;
            pdf[255] = 3;
            pdf[254] = 2;
            pdf[253] = 1;
            vector<float> pdfCopy= smoothGauss1D(pdf, sigma, size);
            pdfMinima = this->localMinima(pdfCopy);
//        }
//    }
    return pdfMinima[0];
}

vector<float> LeafRecognizer::localMinima(vector<float> v)
{
    vector<float> v1;
    vector<float>::iterator itv1 = v1.begin();
    for (int i = 1; i < v.size()-1; ++i)
    {
        if (v[i-1] > v[i] && v[i] < v[i+1])
            itv1 = v1.insert(itv1,i);
    }
    return v1;
}

vector<float> LeafRecognizer::smoothGauss1D(vector<float> v, float sigma, float size)
{
    float offset = 4;
    vector<float> weights(9);
    weights[0] = 0.05;
    weights[1] = 0.07;
    weights[2] = 0.1;
    weights[3] = 0.13;
    weights[4] = 0.3;
    weights[5] = 0.13;
    weights[6] = 0.1;
    weights[7] = 0.07;
    weights[8] = 0.05;
    vector<float> vCopy(v.size()+offset*2);
    for (int i=0; i<offset; ++i)
    {
        vCopy[i] = v[offset-i];
        vCopy[v.size()+i-1] = v[v.size()-1-i];
    }
    for (int i=offset; i<vCopy.size()-offset; ++i)
        vCopy[i] = v[i-offset];
    vector<float> vOut(v);
    for (int i=0; i<v.size(); ++i)
    {
        vector<float> vPart(9);
        vPart[0] = vCopy[i];
        vPart[1] = vCopy[i+1];
        vPart[2] = vCopy[i+2];
        vPart[3] = vCopy[i+3];
        vPart[4] = vCopy[i+4];
        vPart[5] = vCopy[i+5];
        vPart[6] = vCopy[i+6];
        vPart[7] = vCopy[i+7];
        vPart[8] = vCopy[i+8];
        float value = 0;
        for (int j=0; j<vPart.size(); ++j)
        {
            value += vPart[j] * weights[j];
        }
        vOut[i] = value;
    }
    return vOut;
}
