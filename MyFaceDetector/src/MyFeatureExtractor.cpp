#include "MyFeatureExtractor.h"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;


FeatureMat MyFeatureExtractor::extractFeatMat(QFileInfo imInfo, int patchWidth, int patchHeight, QVector<int> &patchRows, QVector<int> &patchCols)
{
    if (!imInfo.exists())
        return FeatureMat();

    Image im = imread(imInfo.filePath().toAscii().constData());
    return extractFeatMat(im, patchWidth, patchHeight, patchRows, patchCols);
}

FeatureMat MyFeatureExtractor::extractFeatMat(Image im, int patchWidth, int patchHeight, QVector<int> &patchRows, QVector<int> &patchCols)
{
    FeatureMat fm;
    int nRowStep = patchHeight;
    int nColStep = patchWidth;
    //int nOverlap=8;
    patchRows.clear();

    for (int idxRow=0; idxRow*nRowStep+patchHeight<im.rows; ++idxRow)
        for (int idxCol=0; idxCol*nColStep+patchWidth<im.cols; ++idxCol)
        {
            int rowStart = idxRow*nRowStep, colStart = idxCol*nColStep;
            patchRows << rowStart;
            patchCols << colStart;
            Image imPatch = im(Rect(colStart, rowStart, patchWidth,patchHeight)).clone();
            int idxPatch = idxRow*patchCols.count() +1 + idxCol;
            FeatureVec fv;
            fv << idxPatch << extractPatch(imPatch);
            fm << fv;
        }
    return fm;
}

FeatureVec MyFeatureExtractor::extractPatch(Image im)
{
    FeatureVec fV;
    fV.clear();
    Image imMono;
    cvtColor(im, imMono, CV_BGR2GRAY);
    imMono.convertTo(imMono, CV_32F);
    fV << getDCT(imMono) << getLOG(imMono) << getHSV(im) << getXY(imMono);
    return fV;
}

FeatureVec MyFeatureExtractor::getDCT(Image I)
{
    Image DCT;
    dct(I, DCT);
    FeatureVec fv;
    fv << DCT.at<float>(0, 0)<< DCT.at<float>(1,0) << DCT.at<float>(0,1) << DCT.at<float>(0,2) << DCT.at<float>(1,1) << DCT.at<float>(2,0) << DCT.at<float>(3,0) << DCT.at<float>(2,1) << DCT.at<float>(1,2) << DCT.at<float>(0,3);
    return fv;
}

FeatureVec MyFeatureExtractor::getLOG(Image I)
{
    Image LOG, im=I;
    im.convertTo(im, CV_8U);
    Laplacian(I, LOG, CV_32F);
    LOG = LOG/4;
    //    reportMat(LOG);
    return getPixels(LOG);
}

FeatureVec MyFeatureExtractor::getHSV(Image I)
{
    Image HSV;
    cvtColor(I, HSV, CV_BGR2HSV);
    HSV.convertTo(HSV, CV_32FC3);
    FeatureVec fv = getPixels(HSV);
    return fv;
}

FeatureVec MyFeatureExtractor::getXY(Image I)
{
    Image X,Y;
    //    Mat el1 = getStructuringElement(MORPH_RECT, Size(3,1), Point(1,0));
    //    morphologyEx(I, buf1, MORPH_DILATE, el1);
    //    morphologyEx(I, buf2, MORPH_ERODE, el1);
    //    X = (buf1-buf2)/2;
    //    Mat el2 = getStructuringElement(MORPH_RECT, Size(1,3), Point(0,1));
    //    morphologyEx(I, buf1, MORPH_DILATE, el2);
    //    morphologyEx(I, buf2, MORPH_ERODE, el2);
    //    Y = (buf1-buf2)/2;
    Sobel(I, X, CV_32F, 1, 0);
    Sobel(I, Y, CV_32F, 0, 1);
    FeatureVec fv;
    //    qDebug("I");
    //    reportMat(I);
    fv << getPixels(X);
    //    fv.append(getPixels(X));
    //    qDebug("X"); reportMat(X);
    fv << getPixels(Y);
    //    fv.append(getPixels(Y));
    //    qDebug("Y"); reportMat(Y);
    return fv;
}

FeatureVec MyFeatureExtractor::getPixels(Image I)
{
    FeatureVec fv;
    if (I.channels()>1)
    {
        std::vector<Image> layers;
        split(I, layers);
        foreach (Image layer, layers)
            fv << getPixels(layer);
        return fv;
    }
    for (int j=0; j<I.rows; ++j)
        for (int i=0; i < I.cols; ++i)
            fv << I.at<float>(i,j);
    return fv;
}
