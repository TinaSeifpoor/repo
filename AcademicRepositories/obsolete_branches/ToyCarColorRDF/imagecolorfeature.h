#ifndef IMAGECOLORFEATURE_H
#define IMAGECOLORFEATURE_H
#include "feature.h"
const int binSize=8;
class ImageColorFeature : public Feature
{
public:
    enum ColorChannel {
        Red=0,
        Green=1,
        Blue=2,
        Hue=3,
        Saturation=4,
        Value=5
    };

    explicit ImageColorFeature(int index=-1);

    int parameterRange() const;
    Feature* getIndex(const int idx) const;
    bool setSource(const Source *samples, const FeatureIdx idxFeature) const;
    int getIndex() const;
private:
    int index;
    int range;

};
typedef QHash<ImageColorFeature::ColorChannel, QList<int> > colorHistograms;
Q_DECLARE_METATYPE(colorHistograms)

#endif // IMAGECOLORFEATURE_H
