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
        int a = 5;
    }

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
            double valIx2 = Ix2.at<double>(idxRow,idxCol);
            double valIy2 = Iy2.at<double>(idxRow,idxCol);
            double valIxy = Ixy.at<double>(idxRow,idxCol);
            if (valIx2!=0 || valIy2!=0 || valIxy!=0)
                int a = 5;
            Harris.at<double>(idxRow, idxCol) = hVal;
        }
    Harris.at<double>(3,3) = double(maxHval);
    return Harris;
}

ContourPoints MyHarris::findLocalMaximaInSquare(Image src, int length, double minTh)
{
    // Label banned items with 1, corners with 255
    uchar ban=1;
    int nRows = src.rows,
        nCols = src.cols;
    int t = src.type();
    imshow("a",src);
    waitKey();
    ContourPoints maximaPoints;
    ContourPoints::iterator itMaximaPoints = maximaPoints.begin();
    Image imComputation(nRows,nCols, CV_8UC1, Scalar(0));
    for (int idxRow = length; idxRow < nRows-length; ++idxRow)
        for (int idxCol = length; idxCol < nCols-length; ++idxCol)
            if (imComputation.at<uchar>(idxRow,idxCol)!=ban)
            {
                double val = src.at<double>(idxRow,idxCol);
                if (val<minTh)
                    break;
                bool isMaxima = true;
                for (int idxLRow = idxRow-length; idxLRow<=length; idxLRow++)
                    if (!isMaxima)
                        break;
                    else
                    {
                        for (int idxLCol = idxCol-length; idxLCol<=length; idxLCol++)
                            if (idxRow == idxLRow && idxCol == idxLCol)
                                continue;
                            else if (val>src.at<double>(idxLRow,idxLCol))
                            {
                                // Ban the current index
                                imComputation.at<uchar>(idxLRow, idxLCol) = ban;
                            }
                            else
                            {
                                // Could ban, but won't return back to this value
                                isMaxima = false;
                                break;
                            }
                    }
                if (isMaxima)
                    // Found corner!
                    itMaximaPoints = maximaPoints.insert(itMaximaPoints, cv::Point(idxRow,idxCol));
//                    imComputation.at<int>(idxRow, idxCol) = corner;
            }
    return maximaPoints;
}
