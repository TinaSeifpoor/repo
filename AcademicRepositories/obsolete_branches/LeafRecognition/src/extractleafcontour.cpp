#include "extractleafcontour.h"

using std::vector;
using cv::Size;

ExtractLeafContour::ExtractLeafContour()
{
}

Contour ExtractLeafContour::segmentExteriorLeafContour(cv::Mat imRGB)
{
    Im imHSV;
    ContourAnalysis ca;
    cv::cvtColor(imRGB, imHSV, CV_RGB2HSV);
    Im im, imGray;
    Im imTh;
    imTh = this->binThreshold(imGray);
    Contour leafExteriorContour, leafExteriorContourCandidates;
    findContours(imTh, leafExteriorContourCandidates, CV_RETR_EXTERNAL , CV_CHAIN_APPROX_SIMPLE);
    ca.selectContoursByArea(leafExteriorContourCandidates, 10000, 10000000, &leafExteriorContour);
    return leafExteriorContour;
}

Im ExtractLeafContour::binThreshold(Im im)
{
    //    Mat imBinTh;
    int histSize = 256;
    float range[] = {0, 256};
    const float* histRange = {range};
    Im histData;
    cv::calcHist(&im, 1, 0, Im(), histData, 1, &histSize, &histRange);
    return im > this->getBinThVal(histData);
}

float ExtractLeafContour::getBinThVal(Im hist)
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


vector<float> ExtractLeafContour::localMinima(vector<float> v)
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

vector<float> ExtractLeafContour::smoothGauss1D(vector<float> v, float sigma, float size)
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

Im ExtractLeafContour::accessChannel(Im im, int idx)
{
    Im imChannel(im.rowRange(0,im.rows-1),im.colRange(0,im.cols-1));
    for (int i=0;i<im.rows;++i)
        for (int j=0;j<im.cols;++j)
            imChannel.at<cv::Vec3b>(i,j) = im.at<cv::Vec3b>(i,j)[idx];
    return imChannel;
}
