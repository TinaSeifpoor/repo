#include "exteriorleafcontourfeatures.h"

ExteriorLeafContourFeatures::ExteriorLeafContourFeatures()
{
}

QList<float> ExteriorLeafContourFeatures::extract(Contour exteriorLeafContour)
{
    QList<float> featureList;
    return featureList <<
                          this->getAspectRatio(exteriorLeafContour) <<
                          this->getRectangularity(exteriorLeafContour) <<
                          this->getCircularity(exteriorLeafContour);
}

float ExteriorLeafContourFeatures::getRectangularity(Contour exteriorLeafContour)
{
    return this->ca.calcRectangularity(exteriorLeafContour[0]);
}

float ExteriorLeafContourFeatures::getAspectRatio(Contour exteriorLeafContour)
{
    return this->ca.calcAspectRatio(exteriorLeafContour)[0];
}

float ExteriorLeafContourFeatures::getCircularity(Contour exteriorLeafContour)
{
    return this->ca.calcCircularity(exteriorLeafContour)[0];
}
