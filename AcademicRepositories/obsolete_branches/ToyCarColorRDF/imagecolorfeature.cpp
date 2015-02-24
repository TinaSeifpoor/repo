#include "imagecolorfeature.h"
#include "opencv2/opencv.hpp"

ImageColorFeature::ImageColorFeature(int index):
    index(index)
{
    if (index ==-1)
        range=((int)Value+1)*binSize;
    else {
        range=1;
    }
}

int ImageColorFeature::parameterRange() const
{
    return this->range;
}

Feature* ImageColorFeature::getIndex(const int idx) const
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
    ColorChannel colorChannel =(ColorChannel)(idxFeature/binSize);
    int bin = idxFeature%binSize;

    for (int idxSamples=0; idxSamples<samples->countSamples(); ++idxSamples) {
        Sample* sample = samples->at(idxSamples);
        sample->featureValues[idxFeature] = sample->sampleSource.value<colorHistograms>().value(colorChannel).at(bin);
    }
    return true;
}
