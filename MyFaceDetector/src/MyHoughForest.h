#ifndef HOUGHFOREST_H
#define HOUGHFOREST_H
#include "MyDecisionForest.h"
#include "FeatureExtractorModel.h"

class HoughForest : public QObject
{
    Q_OBJECT
public:
    HoughForest();
    void setFeatureExtractorModel(FeatureExtractorModel* fe);
    void setDecisionForestModel(DecisionForestModel* df);
    HoughForest(float scaleStep, int scaleCount, float patchOverlap);
    HoughForest(float scaleStep, int scaleCount);
    ~HoughForest();
    QVector<cv::Rect> getFace(QFileInfo imInfo);
    QVector<cv::Rect> getFace(Image im);

private:
    float scaleStep;
    float patchOverlap;
    int scaleCount;
    FeatureExtractorModel* fe;
    DecisionForestModel* df;
};



#endif // HOUGHFOREST_H
