#ifndef IMAGECOLORFEATURES_H
#define IMAGECOLORFEATURES_H
#include "features.h"

class ImageColorFeatures : public Features
{
public:
    ImageColorFeatures();

    Features* copy(QHash<int, Feature *> featureList) const;
    ImageColorFeatures(Feature *feature);
    ImageColorFeatures(QHash<int,Feature *> features);
    void calculateFeatureValues(FeatureIdx featureIdx);
};

#endif // IMAGECOLORFEATURES_H
