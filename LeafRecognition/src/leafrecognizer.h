#ifndef LEAFRECOGNIZER_H
#define LEAFRECOGNIZER_H
#include "contouranalysis.h"
#include "myotsu.h"
#include <QVariantHash>
class LeafRecognizer
{
public:
    LeafRecognizer(cv::Mat im);
    QVariantHash getLeafFeatures(cv::Mat *imOut);
private:
    float getExteriorRectangularity();
    float getAspectRatio();
    cv::Mat binThreshold(cv::Mat im);
    float getBinThVal(cv::Mat histData);
    std::vector<float> localMinima(std::vector<float> v);
    std::vector<float> smoothGauss1D (std::vector<float> pdf, float sigma, float size);

    Contour getSmallestRectangle (Contour contours);
    cv::Mat im;
    Contour leafExteriorContour;
ContourAnalysis ca;
};

#endif // LEAFRECOGNIZER_H
