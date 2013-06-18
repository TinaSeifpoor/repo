//#ifndef MYDECISIONFORESTCV_H
//#define MYDECISIONFORESTCV_H
//#include <QStringList>

//#include <opencv2/core/core.hpp>
//typedef int Label;
//typedef double Feature;
//typedef cv::Mat FeatureVec;
//typedef cv::Mat FeatureMat;
//typedef cv::Mat ClassCounts;
//struct MyNode
//{
//    double th;
//    ClassCounts classDistributions;
//    int F1;
//    int F2;
//};

//typedef QList<MyNode> MyTree;
//typedef QList<MyTree> MyForest;
//class MyDecisionForestCV
//{
//public:
//    MyDecisionForestCV();
//    void readForest(QString forestText);
//    void trainSample(QString sampleText);
//    void trainSampleMat(FeatureMat featMat);
//    QString dumpForest ();
//    QList<Label> testSampleMat(FeatureMat featMat);
//    QList<ClassCounts> testSampleMatCC(FeatureMat featMat);
//    Label testForest(FeatureVec featVec);
//    ClassCounts testForestCC(FeatureVec featVec);
//    double testSampleMatPerf(FeatureMat featMat);

//private:
//    MyTree readTree(QString treeText);
//    MyNode readNode(QString nodeText);
//    void populateForest (FeatureVec featVec, Label l);
//    void addSampleToTree(FeatureVec featVec, Label l, int idxTree, int idxNode=1);
//    ClassCounts testSampleAtTree(FeatureVec featVec, int idxTree, int idxNode=1);
//    MyForest forest;
//};

//#endif // MYDECISIONFORESTCV_H
