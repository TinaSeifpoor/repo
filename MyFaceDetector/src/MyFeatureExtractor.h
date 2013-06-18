#ifndef MYFEATUREEXTRACTOR_H
#define MYFEATUREEXTRACTOR_H

#include <QFileInfo>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QVector>
#include <FeatureExtractorModel.h>

class MyFeatureExtractor : public FeatureExtractorModel
{
public:
    MyFeatureExtractor(){}
    FeatureMat extractFeatMat (Image im, int patchWidth, int patchHeight, QVector<int> &patchRows, QVector<int> &patchCols);
    FeatureMat extractFeatMat (QFileInfo imInfo, int patchWidth, int patchHeight, QVector<int> &patchRows, QVector<int> &patchCols);

private:
    FeatureVec extractPatch(Image im);
    FeatureVec getDCT(Image I);
    FeatureVec getLOG(Image I);
    FeatureVec getHSV(Image I);
    FeatureVec getXY(Image I);

    FeatureVec getPixels(Image I);

};

#endif // MYFEATUREEXTRACTOR_H
