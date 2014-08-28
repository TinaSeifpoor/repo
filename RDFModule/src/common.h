#ifndef COMMON_H
#define COMMON_H

typedef int ClassID;
typedef int FeatureIdx;
typedef double FeatureValue;
#include <QStringList>
#include <QVariant>

struct TreeProperties
{
    double  baggingFactorFeatures,
            baggingFactorSamples;
    int maxDepth;
};

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

struct ForestProperties
{


    int    nTrees;
    double          baggingFactorFeatures,
                    baggingFactorSamples;
    TreeProperties  treeProperties;
    void set(QString var, QString val) {
        if (var == BaggingFactorFeaturesTree)
            baggingFactorFeatures=val.toDouble();
        if (var == BaggingFactorSamplesTree)
            baggingFactorSamples=val.toDouble();
        if (var == ForestSize)
            nTrees=val.toInt();
        if (var == MaxDepth)
            treeProperties.maxDepth=val.toInt();
        if (var == BaggingFactorFeaturesNode)
            treeProperties.baggingFactorFeatures=val.toDouble();
        if (var == BaggingFactorSamplesNode)
            treeProperties.baggingFactorSamples=val.toDouble();
    }

    void setAll(QString text) {
        QStringList forestPropertiesKeywords = QStringList()    << BaggingFactorFeaturesTree
                                                                << BaggingFactorFeaturesTree
                                                                << BaggingFactorSamplesTree
                                                                << ForestSize
                                                                << BaggingFactorFeaturesNode
                                                                << BaggingFactorSamplesNode
                                                                << MaxDepth;
        foreach (QString forestPropertiesKeyword, forestPropertiesKeywords) {
            QString beginText = forestPropertiesKeyword;
            beginText.prepend("<");
            beginText.append(">");
            QString endText = forestPropertiesKeyword;
            endText.append(">");
            endText.prepend("</");
            int beginInd = text.indexOf(beginText);
            int endInd = text.indexOf(endText);
            QString propertyValue = text.mid(beginInd+beginText.length(), endInd-beginInd-beginText.length());
            set(forestPropertiesKeyword,propertyValue);
        }
    }
};
template<typename T>
QPair<QList<int>, QList<T> > getSampleHistogram(QList<T> list) {
    QList<int> histogram;
    QList<T> uniqueList;
    foreach (T item, list) {
        if (!uniqueList.contains(item)) {
            uniqueList.append(item);
            histogram.append(1);
        } else {
            int idx = uniqueList.indexOf(item);
            histogram[idx]++;
        }
    }
    return qMakePair<QList<int>, QList<T>>(histogram, uniqueList);
}

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

class TestResult {
public:
    TestResult() {treeIdx = 0;}
    void setTreeIndex(int treeIdx) {
        this->treeIdx = treeIdx;
    }

    void add(QString testSampleId, int nodeDepth, QHash<QString, ClassID> trainSampleIDHash) {
        TreeResult t;
        t.treeDepth = nodeDepth;
        t.trainSampleIDHash = trainSampleIDHash;
        t.treeIdx = treeIdx;
        container.insertMulti(testSampleId,t);
    }

    ClassID getSampleClassMajority (QString sampleID) {
        QList<TreeResult> treeResults = container.values(sampleID);
        QList<ClassID> classList;
        foreach (TreeResult result, treeResults) {
            classList+=result.trainSampleIDHash.values();
        }
        QPair<QList<ClassID>,QList<int>> histogram = getSampleHistogram(classList);
        int maxCount = -1;
        ClassID classChosen;
        for (int i=0; i<histogram.second.count();++i) {
            if (histogram.second.at(i)>maxCount) {
                maxCount = histogram.first.at(i);
                classChosen = histogram.second.at(i);
            }
        }
        return classChosen;
    }

private:
    QHash<QString, TreeResult> container;
    int treeIdx;
};

#endif // COMMON_H
