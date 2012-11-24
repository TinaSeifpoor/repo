#ifndef MYFEATUREDETECTOR_H
#define MYFEATUREDETECTOR_H
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;
class HarrisCornerDetector: public cv::FeatureDetector
{
    typedef cv::Mat Image;
public:
    void detect( const cv::Mat& image, std::vector<cv::KeyPoint>& keyPoints,
                                        const cv::Mat& mask=cv::Mat() ) const;
//    void detect( const std::vector<cv::Mat&> image, std::vector<std::vector<cv::KeyPoint> >& keyPoints,
//                 const std::vector<cv::Mat&> masks = std::vector<cv::Mat>() ) const;

    void detectImpl( const Mat& image, vector<KeyPoint>& keypoints, const Mat& mask=Mat() ) const;

private:
    void calcSmoothDeriv(const Image src, Image *Ix2, Image *Ixy, Image *Iy2, double sigma=5, int kernelSize=31) const;
    Image cornerHarrisM(const Image Ix2,const  Image Ixy,const  Image Iy2, double k=0.04) const;
    std::vector<cv::KeyPoint> findLocalMaximaInSquare(const Image src, const cv::Mat& mask, int length=10, double minTh=500, unsigned int nPoints=0) const;
};

#endif // MYFEATUREDETECTOR_H
