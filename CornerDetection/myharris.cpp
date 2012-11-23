#include "myharris.h"
using std::string;
using namespace cv;
MyHarris::MyHarris(const string filePath)
{
    Image im = imread(filePath);
    int nChannels = im.channels();
    vector<Image> imChannels;
    imChannels.resize(nChannels);
    split(im, imChannels);
    for (int idxCh=0; idxCh<nChannels; ++idxCh)
    {
        Image Ix2, Ixy, Iy2;
        calcSmoothDeriv(imChannels[idxCh], &Ix2, &Ixy, &Iy2);
//        imshow("a", Ix2);
//        imshow("b", Iy2);
//        imshow("c", Ixy);
//        waitKey();
        ContourPoints cornerPoints = findLocalMaximaInSquare(cornerHarrisM(Ix2, Ixy, Iy2));
        drawOnImage(im,cornerPoints,(0,200,200));
        int a = 5;
    }
    imshow("a",im);
    waitKey();
}

void MyHarris::calcSmoothDeriv(Image src, Image *Ix2, Image *Ixy, Image *Iy2, int sigma, int kernelSize)
{
    Image iX, iY;
    Sobel(src, iX, CV_64F, 1, 0);
    GaussianBlur( iX, iX, Size(kernelSize,kernelSize), sigma, sigma);

    Sobel(src, iY, CV_64F, 0, 1);
    GaussianBlur( iY, iY, Size(kernelSize,kernelSize), sigma, sigma);

    cv::pow(iX,2,*Ix2);
    *Ixy = iX.mul(iY);
    cv::pow(iY,2,*Iy2);
}

Image MyHarris::cornerHarrisM(Image Ix2, Image Ixy, Image Iy2, double k)
{
    int nRows = Ix2.rows;
    int nCols = Ix2.cols;
    Image Harris(nRows,nCols, CV_64F);
    double maxHval=-555555;
    for (int idxRow = 0; idxRow < nRows; ++idxRow)
        for (int idxCol = 0; idxCol < nCols; ++idxCol)
        {
            double hVal = -(Ix2.at<double>(idxRow,idxCol)*Iy2.at<double>(idxRow,idxCol) - Ixy.at<double>(idxRow,idxCol) * Ixy.at<double>(idxRow, idxCol) - k*(Ix2.at<double>(idxRow,idxCol)+Iy2.at<double>(idxRow,idxCol))*(Ix2.at<double>(idxRow,idxCol)+Iy2.at<double>(idxRow,idxCol)));
            if(hVal>maxHval)
                maxHval = hVal;
//            double valIx2 = Ix2.at<double>(idxRow,idxCol);
//            double valIy2 = Iy2.at<double>(idxRow,idxCol);
//            double valIxy = Ixy.at<double>(idxRow,idxCol);
//            if (valIx2!=0 || valIy2!=0 || valIxy!=0)
//                int a = 5;
            Harris.at<double>(idxRow, idxCol) = hVal;
        }
    Harris = maxHval-Harris;
    return Harris;
}

ContourPoints MyHarris::findLocalMaximaInSquare(Image src, int length, double minTh, int nPoints)
{
    // Label banned items with 1, corners with 255
    uchar ban=1;
    int nRows = src.rows,
        nCols = src.cols;
//    int t = src.type();
//    Image imTh = src>minTh;
//        imshow("a",imTh);
//        waitKey();
    ContourPoints maximaPoints;
    vector<double> maximaPointValues;
    Image imComputation(nRows,nCols, CV_8UC1, Scalar(0));
    bool pointsFull = false;
    for (int idxRow = length; idxRow < nRows-length; ++idxRow)
    {
        for (int idxCol = length; idxCol < nCols-length; ++idxCol)
        {
            if (imComputation.at<uchar>(idxRow,idxCol)!=ban)
            {
                double val = src.at<double>(idxRow,idxCol);
                if ((pointsFull && val<=maximaPointValues.back()) || (val<minTh) )
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
                    int nPointsFound = maximaPointValues.size();
                    vector<double>::iterator itVal = maximaPointValues.begin();
                    ContourPoints::iterator itPoi = maximaPoints.begin();
                    bool pointAdded=false;
                    for (int idxVal = 0; idxVal<nPointsFound; ++idxVal)
                    {
                        if (maximaPointValues[idxVal]<val)
                        {
                            maximaPointValues.insert(itVal, val);
                            maximaPoints.insert(itPoi, cv::Point(idxCol,idxRow));
                            pointAdded=true;
                            break;
                        }
                        ++itVal; ++itPoi;
                    }
                    if(!pointAdded)
                    {
                        maximaPoints.insert(maximaPoints.end(), cv::Point(idxCol,idxRow));
                        maximaPointValues.insert(maximaPointValues.end(), val);
                    }
                    if (maximaPointValues.size()==nPoints)
                        pointsFull=true;
                    else if (maximaPointValues.size()>nPoints)
                    {
                        maximaPointValues.erase(--maximaPointValues.end(),maximaPointValues.end());
                        maximaPoints.erase(--maximaPoints.end(),maximaPoints.end());
                    }
                }
            }
        }
    }
    return maximaPoints;
}

void MyHarris::drawOnImage(Image &image, const ContourPoints &points, Scalar color, int radius, int thickness)
{
    std::vector<cv::Point>::const_iterator it= points.begin();

             // for all corners
             while (it!=points.end()) {

                 // draw a circle at each corner location
                 cv::circle(image,*it,radius,color,thickness);
                 ++it;
             }
}
