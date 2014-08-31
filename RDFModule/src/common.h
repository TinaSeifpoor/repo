#ifndef COMMON_H
#define COMMON_H
#include "rdfmodule_global.h"
typedef int ClassID;
typedef int FeatureIdx;
typedef double FeatureValue;
#include <QStringList>
#include <QVariant>
static const char* BaggingFactorFeaturesTree    ="BaggingFactorFeaturesTree";
static const char* BaggingFactorSamplesTree     ="BaggingFactorSamplesTree";
static const char* ForestSize                   ="ForestSize";
static const char* BaggingFactorFeaturesNode    ="BaggingFactorFeaturesNode";
static const char* BaggingFactorSamplesNode     ="BaggingFactorSamplesNode";
static const char* MaxDepth                     ="MaxDepth";

static const char* TreeText                     = "Tree";
static const char* NodeText                     = "Node";
static const char* EntropyText                  = "Entropy";
static const char* LeftUniqueClassesText        = "LeftUniqueClasses";
static const char* RightUniqueClassesText       = "RightUniqueClasses";
static const char* LeftSampleClassesText        = "LeftSampleClasses";
static const char* RightSampleClassesText       = "RightSampleClasses";
static const char* FeatureIdxText               = "FeatureIdx";
static const char* SplitValueText               = "SplitValue";

struct TreeProperties
{
    double  baggingFactorFeatures,
            baggingFactorSamples;
    int maxDepth;
};


struct ForestProperties
{


    int    nTrees;
    double          baggingFactorFeatures,
                    baggingFactorSamples;
    TreeProperties  treeProperties;
    void set(QString var, QString val);

    void setAll(QString text);
};

template<typename T>
QPair<QList<int>, QList<T> > getSampleHistogram(QList<T> list);

struct Sample {
    QVariant sampleSource;
    ClassID sampleClass;
    QHash<FeatureIdx, FeatureValue> featureValues;
    QString sampleId;
};

struct TreeResult {
    int treeDepth;
    QHash<QString, ClassID> trainSampleIDHash;
    int treeIdx;
};

class RDFMODULESHARED_EXPORT TestResult {
public:
    TestResult() {treeIdx = 0;}
    void setTreeIndex(int treeIdx);

    void add(QString testSampleId, int nodeDepth, QHash<QString, ClassID> trainSampleIDHash);

    ClassID getSampleClassMajority (QString sampleID);

private:
    QHash<QString, TreeResult> container;
    int treeIdx;
};

#endif // COMMON_H
