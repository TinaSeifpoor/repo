#ifndef EXTRACTLEAFCONTOUR_H
#define EXTRACTLEAFCONTOUR_H
#include "contouranalysis.h"

class ExtractLeafContour
{
public:
    ExtractLeafContour();

    Contour segmentExteriorLeafContour(Im im);
private:
    Im binThreshold(Im im);
    float getBinThVal(Im histData);
    std::vector<float> localMinima(std::vector<float> v);
    std::vector<float> smoothGauss1D (std::vector<float> pdf, float sigma, float size);


};

#endif // EXTRACTLEAFCONTOUR_H
