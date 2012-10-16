#ifndef LEAFRECOGNIZER_H
#define LEAFRECOGNIZER_H
#include "contouranalysis.h"
#include "myotsu.h"
class LeafRecognizer
{
public:
    LeafRecognizer();
    void recognize(cv::Mat im);
private:
    cv::Mat binThreshold(cv::Mat im);
    float getBinThVal(cv::Mat histData);
    std::vector<float> localMinima(std::vector<float> v);
    std::vector<float> smoothGauss1D (std::vector<float> pdf, float sigma, float size);
};

#endif // LEAFRECOGNIZER_H
