#ifndef MYHARRIS_H
#define MYHARRIS_H
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
typedef cv::Mat Image;
typedef std::vector<cv::Point> ContourPoints;
typedef std::vector<ContourPoints> Contour;

class MyHarris
{
public:
    MyHarris(const std::string filePath);
private:
    void calcSmoothDeriv(Image src, Image *Ix2, Image *Ixy, Image *Iy2, int sigma=0.5, int kernelSize=7);
    Image cornerHarrisM(Image Ix2, Image Ixy, Image Iy2, double k=0.05);
    ContourPoints findLocalMaximaInSquare(Image src, int length=3, double minTh=0.05);
};

#endif // MYHARRIS_H
