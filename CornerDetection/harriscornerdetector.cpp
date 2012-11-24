#include "harriscornerdetector.h"
using std::string;
using std::vector;
using namespace cv;
typedef unsigned int uint;
typedef std::vector<cv::KeyPoint> KeyPoints;

typedef cv::Mat Image;


void HarrisCornerDetector::calcSmoothDeriv(const Image imSrc, Image *ImX2, Image *ImXY, Image *ImY2, double sigma, uint kernelSize) const
{
    Image imSmooth;
    GaussianBlur(imSrc, imSmooth, Size(kernelSize,kernelSize), sigma, sigma);
    Image imX, imY;
    Scharr(imSmooth, imX, CV_64F, 1, 0);
    GaussianBlur(imX, imX, Size(kernelSize,kernelSize), sigma, sigma);
    Scharr(imSmooth, imY, CV_64F, 0, 1);
    GaussianBlur(imY, imY, Size(kernelSize,kernelSize), sigma, sigma);

    cv::pow(imX,2,*ImX2);
    *ImXY = imX.mul(imY);
    cv::pow(imY,2,*ImY2);
}

Image HarrisCornerDetector::cornerHarrisM(const Image Ix2, const Image Ixy, const Image Iy2, double k) const
{
    Image det, tra, har;
    subtract(Ix2.mul(Iy2), Ixy.mul(Ixy), det);
    Image Ix2PIy2;
    add(Ix2,Iy2,Ix2PIy2);
    tra = -k*Ix2PIy2.mul(Ix2PIy2);
    subtract(det, tra, har);
    return har;
}

KeyPoints HarrisCornerDetector::findLocalMaximaInSquare(const Image src, const Mat &mask, uint length, double minTh, uint nKeyPoints) const
{
    // Label banned items with ban
    uchar ban=255;
    uint nRows = src.rows,
        nCols = src.cols;
    KeyPoints keyPoints;
    // Ban points outside mask and values (in src) below minTh
    Image imBan(src.size(), CV_8U, Scalar(0));
    imBan = (src<minTh);
    if (!mask.empty())
    {
        Image imBanMask;
        bitwise_not(mask, imBanMask);
        // remove borders on the mask with length
        dilate(imBanMask, imBanMask, getStructuringElement(MORPH_RECT, Size(length,length)));
        bitwise_or(imBan, imBanMask, imBan);
    }
    //
    bool pointsFull = false;
    for (uint idxRow = length; idxRow < nRows-length; ++idxRow)
    {
        for (uint idxCol = length; idxCol < nCols-length; ++idxCol)
        {
            if (imBan.at<uchar>(idxRow,idxCol)==ban)
                continue;
            double val = src.at<double>(idxRow,idxCol);
            if (pointsFull && val<=keyPoints.back().response)
                continue;
            bool isMaxima = true;
            for (uint idxLRow = idxRow-length; idxLRow<=idxRow+length; idxLRow++)
            {
                if (!isMaxima)
                    break;
                else
                {
                    for (uint idxLCol = idxCol-length; idxLCol<=idxCol+length; idxLCol++)
                        if (idxRow == idxLRow && idxCol == idxLCol)
                            continue;
                        else if (val>=src.at<double>(idxLRow,idxLCol))
                        {
                            // Ban the current index
                            imBan.at<uchar>(idxLRow, idxLCol) = ban;
                        }
                        else
                        {
                            isMaxima = false;
                            break;
                        }
                }
            }
            if (isMaxima)
            {
                // Found corner!
                bool pointAdded=false;
                for (KeyPoints::iterator itPoi=keyPoints.begin(); itPoi!=keyPoints.end(); ++itPoi)
                {
                    if ((*itPoi).response<val)
                    {
                        keyPoints.insert(itPoi, cv::KeyPoint((float)idxCol,(float)idxRow, (float)length, (float)-1,(float)val));
                        pointAdded=true;
                        break;
                    }
                }
                if(!pointAdded)
                {
                    keyPoints.push_back(cv::KeyPoint((float)idxCol,(float)idxRow, (float)length, (float)-1,(float)val));
                }
                if (nKeyPoints)
                {
                    if (keyPoints.size()==nKeyPoints)
                    {
                        pointsFull=true;
                    }
                    else if (keyPoints.size()>nKeyPoints)
                    {
                        keyPoints.pop_back();
                    }
                }
            }
        }
    }
    return keyPoints;
}


void HarrisCornerDetector::detect(const Mat &image, KeyPoints &keyPoints, const Mat &mask) const
{

    uint nChannels = image.channels();
    Mat imageGray;
    // TODO should consider calculating key points from color space, like lab instead of just gray
    if (nChannels == 3)
        cv::cvtColor(image, imageGray, CV_BGR2GRAY);
    else
        image.copyTo(imageGray);
    this->detectImpl(imageGray, keyPoints, mask);
    return;
}

void HarrisCornerDetector::detectImpl(const Mat &image, KeyPoints &keypoints, const Mat &mask) const
{
    Mat Ix2, Ixy, Iy2;
    calcSmoothDeriv(image, &Ix2, &Ixy, &Iy2);
    keypoints = findLocalMaximaInSquare(cornerHarrisM(Ix2, Ixy, Iy2), mask);
}
