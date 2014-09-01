#include "imagecolorfeature.h"
#include "opencv2/opencv.hpp"
enum ImageColorEnum {
    Red,
    Green,
    Blue,
    Hue,
    Saturation,
    Value
};

ImageColorFeature::ImageColorFeature(int index):
    index(index)
{
    if (index ==-1)
        range=1500;
    else {
        range=1;
    }
}

int ImageColorFeature::parameterRange() const
{
    return this->range;
}

Feature* ImageColorFeature::getIndex() const
{
    if (this->index==-1 && range>idx) {
        return new ImageColorFeature(idx);
    } else if (idx == 0){
        return new ImageColorFeature(index);
    }
    return 0;
}

int ImageColorFeature::getIndex() const
{
    if (range == 1) {
        return this->index;
    } else {
        return -1;
    }
}


bool ImageColorFeature::setSource(const Source *samples, const FeatureIdx idxFeature) const
{
    switch ((ImageColorEnum)idxFeature) {
    case Red:
        break;
    case Green:
        break;
    case Blue:
        break;
    case Hue:
        break;
    case Saturation:
        break;
    case Value:
        break;
    }

    for (int idxSamples=0; idxSamples<samples->countSamples(); ++idxSamples) {
        Sample* sample = samples->at(idxSamples);
        if (!sample->featureValues.contains(idxFeature)) {
            cv::Mat image = sample->sampleSource.value<cv::Mat>();
            image.

            int featureVal = sample->sampleClass&feature;
            sample->featureValues[idxFeature] = (getRand()-0.5)+featureVal;
        }
    }
    return true;
}
