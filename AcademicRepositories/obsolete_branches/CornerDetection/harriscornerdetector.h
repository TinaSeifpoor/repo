#ifndef MYFEATUREDETECTOR_H
#define MYFEATUREDETECTOR_H
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

class HarrisCornerDetector: public cv::FeatureDetector
{
    // All definitions
    typedef cv::Mat Image;
    typedef std::vector<cv::KeyPoint> KeyPoints;
    typedef unsigned int uint;
    // All definitions

public:
    void detect( const Image& image, KeyPoints& keyPoints,
                                        const Image& mask=Image() ) const;


private:
    void detectImpl( const Image& image, KeyPoints& keypoints, const Image& mask=Image() ) const;
    void calcSmoothDeriv(const Image src, Image *ImX2, Image *ImXY, Image *ImY2,
                         double sigma=2.31, uint smoothKernelSize=11, uint medianKernelSize=5) const;
    Image cornerHarrisM(const Image Ix2, const  Image Ixy, const  Image Iy2, double k=0.04,
                        uint smoothKernelSize=11, double sigma=2.31) const;
    KeyPoints findLocalMaximaInSquare(const Image src, const Image& mask,
                                                      uint length=3, double minTh=500, uint nPoints=150) const;
};

#endif // MYFEATUREDETECTOR_H
