#ifndef MYDECISIONFOREST_H
#define MYDECISIONFOREST_H
#include <QStringList>
#include <DecisionForestModel.h>

struct MyNode
{
    double th;
    ClassDistribution classDistributions;
    int F1;
    int F2;
};

typedef QVector<MyNode> MyTree;
typedef QVector<MyTree> MyForest;

class MyDecisionForest : public DecisionForestModel
{
public:
    MyDecisionForest(){}
    void readForest(QString forestText);
    QVector<ClassDistribution> testSampleMatCC(FeatureMat featMat);
    void testForestCC();

    void trainSample(QString sampleText);
    void trainSampleMat(FeatureMat featMat);
    QString dumpForest ();
    QVector<Label> testSampleMat(FeatureMat featMat);
    Label testForest(FeatureVec featVec);
    double testSampleMatPerf(FeatureMat featMat);
protected:

private:
    MyTree readTree(QString treeText);
    MyNode readNode(QString nodeText);
    void populateForest (FeatureVec featVec, Label l);
    void addSampleToTree(FeatureVec featVec, Label l, int idxTree, int idxNode=1);
    ClassDistribution testSampleAtTree(FeatureVec featVec, int idxTree, int idxNode=1);
    void testSampleAtTreeCC(int idxTree, int idxNode=1);
    MyForest forest;
    AllClassDistribution acd;
};

#endif // MYDECISIONFOREST_H
