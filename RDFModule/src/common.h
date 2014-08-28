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
static const char* UniqueClassesText            = "UniqueClasses";
static const char* ClassesText                  = "Classes";
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

struct Sample {
    QVariant sampleSource;
    ClassID sampleClass;
    QHash<FeatureIdx, FeatureValue> featureValues;
};

#endif // COMMON_H
