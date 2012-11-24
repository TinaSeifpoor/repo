#include "harriscornerdetector.h"
using std::string;
using std::vector;
using namespace cv;

typedef cv::Mat Image;


void HarrisCornerDetector::calcSmoothDeriv(const Image src, Image *Ix2, Image *Ixy, Image *Iy2, double sigma, int kernelSize) const
{
    Image iX, iY;
    Sobel(src, iX, CV_64F, 1, 0, CV_SCHARR);
    GaussianBlur( iX, iX, Size(kernelSize,kernelSize), sigma, sigma);

    Sobel(src, iY, CV_64F, 0, 1, CV_SCHARR);
    GaussianBlur( iY, iY, Size(kernelSize,kernelSize), sigma, sigma);

    cv::pow(iX,2,*Ix2);
    *Ixy = iX.mul(iY);
    cv::pow(iY,2,*Iy2);
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

vector<KeyPoint> HarrisCornerDetector::findLocalMaximaInSquare(const Image src, const Mat &mask, int length, double minTh, unsigned int nKeyPoints) const
{
    typedef std::vector<cv::KeyPoint> KeyPoints;
    typedef std::vector<double> KeyPointValues;
    // Label banned items with 1, corners with 255
    uchar ban=255;
    int nRows = src.rows,
        nCols = src.cols;
    KeyPoints keyPoints;
    KeyPointValues keyPointValues;
    Image imComputation(nRows, nCols, CV_8UC1, Scalar(0));
    if (!mask.empty())
        imComputation = mask<1;

    bool pointsFull = false;
    for (int idxRow = length; idxRow < nRows-length; ++idxRow)
    {
        for (int idxCol = length; idxCol < nCols-length; ++idxCol)
        {
            if (imComputation.at<uchar>(idxRow,idxCol)!=ban)
            {
                double val = src.at<double>(idxRow,idxCol);
                if ((pointsFull && val<=keyPointValues.back()) || (val<minTh) )
                    continue;
                bool isMaxima = true;
                for (int idxLRow = idxRow-length; idxLRow<=idxRow+length; idxLRow++)
                    if (!isMaxima)
                        break;
                    else
                    {
                        for (int idxLCol = idxCol-length; idxLCol<=idxCol+length; idxLCol++)
                            if (idxRow == idxLRow && idxCol == idxLCol)
                                continue;
                            else if (val>=src.at<double>(idxLRow,idxLCol))
                            {
                                // Ban the current index
                                imComputation.at<uchar>(idxLRow, idxLCol) = ban;
                            }
                            else
                            {
                                isMaxima = false;
                                break;
                            }
                    }
                if (isMaxima)
                {
                    // Found corner!
                    int nPointsFound = keyPointValues.size();
                    KeyPointValues::iterator itVal = keyPointValues.begin();
                    KeyPoints::iterator itPoi = keyPoints.begin();
                    bool pointAdded=false;
                    for (int idxVal = 0; idxVal<nPointsFound; ++idxVal)
                    {
                        if (keyPointValues[idxVal]<val)
                        {
                            keyPointValues.insert(itVal, val);
                            keyPoints.insert(itPoi, cv::KeyPoint((float)idxCol,(float)idxRow, (float)length, (float)-1,(float)val));
                            pointAdded=true;
                            break;
                        }
                        ++itVal; ++itPoi;
                    }
                    if(!pointAdded)
                    {
                        keyPoints.insert(keyPoints.end(), cv::KeyPoint((float)idxCol,(float)idxRow, (float)length, (float)-1,(float)val));
                        keyPointValues.insert(keyPointValues.end(), val);
                    }
                    if (nKeyPoints)
                    {
                        if (keyPointValues.size()==nKeyPoints)
                            pointsFull=true;
                        else if (keyPointValues.size()>nKeyPoints)
                        {
                            keyPointValues.erase(--keyPointValues.end(),keyPointValues.end());
                            keyPoints.erase(--keyPoints.end(),keyPoints.end());
                        }
                    }
                }
            }
        }
    }
    return keyPoints;
}


void HarrisCornerDetector::detect(const Mat &image, std::vector<KeyPoint> &keyPoints, const Mat &mask) const
{
    this->detectImpl(image, keyPoints, mask);
//    int nChannels = image.channels();
//    Mat imOut;
//    image.copyTo(imOut);
//    vector<Image> imChannels;
//    imChannels.resize(nChannels);
//    split(imOut, imChannels);
//    for (int idxCh=0; idxCh<nChannels; ++idxCh)
//    {

//        drawOnImage(imOut,keypoints,Scalar(0,255,255), 1, 1);
//    }
//            imshow("a",imOut);
//            waitKey();
    return;
}

void HarrisCornerDetector::detectImpl(const Mat &image, vector<KeyPoint> &keypoints, const Mat &mask) const
{
    Mat Ix2, Ixy, Iy2;
    calcSmoothDeriv(image, &Ix2, &Ixy, &Iy2);
    keypoints = findLocalMaximaInSquare(cornerHarrisM(Ix2, Ixy, Iy2), mask);
}
