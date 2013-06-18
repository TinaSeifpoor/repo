#ifndef FEATUREEXTRACTORMODEL_H
#define FEATUREEXTRACTORMODEL_H
#include <QVector>
#include <QFileInfo>
#include <cv.hpp>
typedef float Feature;
typedef QVector<Feature> FeatureVec;
typedef QVector<FeatureVec> FeatureMat;
typedef cv::Mat Image;

class FeatureExtractorModel
{
public:
    FeatureExtractorModel(){}
    ~FeatureExtractorModel(){}
    virtual FeatureMat extractFeatMat (Image im, int patchWidth, int patchHeight, QVector<int> &patchRows, QVector<int> &patchCols)=0;
    virtual FeatureMat extractFeatMat (QFileInfo imInfo, int patchWidth, int patchHeight, QVector<int> &patchRows, QVector<int> &patchCols)=0;
};


#endif // FEATUREEXTRACTORMODEL_H
