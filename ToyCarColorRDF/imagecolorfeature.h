#ifndef IMAGECOLORFEATURE_H
#define IMAGECOLORFEATURE_H
#include "feature.h"
class ImageColorFeature : public Feature
{
public:
    explicit ImageColorFeature(int index=-1);

    int parameterRange() const;
    Feature* getIndex(const int idx) const;
    bool setSource(const Source *samples, const FeatureIdx idxFeature) const;
    int getIndex() const;
private:
    int index;
    int range;

};

#endif // IMAGECOLORFEATURE_H
