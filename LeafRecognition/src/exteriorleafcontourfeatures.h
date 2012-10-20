#ifndef EXTERIORLEAFCONTOURFEATURES_H
#define EXTERIORLEAFCONTOURFEATURES_H
#include "contouranalysis.h"
#include <QList>
class ExteriorLeafContourFeatures
{
public:
    ExteriorLeafContourFeatures();
    QList<float> extract(Contour exteriorLeafContour);
private:
    float getRectangularity(Contour exteriorLeafContour);
    float getAspectRatio(Contour exteriorLeafContour);
    float getCircularity(Contour exteriorLeafContour);
    ContourAnalysis ca;

};

#endif // EXTERIORLEAFCONTOURFEATURES_H
