#ifndef DECISIONFORESTMODEL_H
#define DECISIONFORESTMODEL_H
#include <QVector>
typedef int Label;
typedef float Feature;
typedef QVector<Feature> FeatureVec;
typedef QVector<FeatureVec> FeatureMat;
typedef QVector<Label> ClassDistribution;
typedef QVector<QVector<QVector<Label> > > AllClassDistribution;

struct ForestProperties
{
    int nFeatures, nClasses;
    QVector<int> patchOffsetsRows, patchOffsetsCols;
    int maxOffsetRow, maxOffsetCol;
    int patchHeight, patchWidth;
    int BBHeight, BBWidth;
};
class DecisionForestModel
{
public:
    DecisionForestModel(){}
    ~DecisionForestModel(){}
    virtual void readForest(QString forestText)=0;
    virtual QVector<ClassDistribution> testSampleMatCC(FeatureMat featMat)=0;
    virtual void testForestCC()=0;
    ForestProperties forestModel;
    ClassDistribution cc;
    FeatureVec featVec;

};

#endif // DECISIONFORESTMODEL_H
