#include "imagecolorfeatures.h"
#include "imagecolorfeature.h"
ImageColorFeatures::ImageColorFeatures()
{
    this->init();
    (*this) << new ImageColorFeature;
}

Features *ImageColorFeatures::copy(QHash<int,Feature *> featureList) const
{
    return new ImageColorFeatures(featureList);
}


ImageColorFeatures::ImageColorFeatures(Feature *feature)
{
    this->init();
    (*this) << feature;
}
ImageColorFeatures::ImageColorFeatures(QHash<int, Feature *> features)
{
    this->init();
    foreach (int i, features.keys())
        (*this) << features.value(i);
}

void ImageColorFeatures::calculateFeatureValues(FeatureIdx featureIdx)
{
    ImageColorFeature* ft = dynamic_cast<ImageColorFeature*>(Features::at(featureIdx));
    if (ft)
        ft->setSource(getSamples(),featureIdx);
}
