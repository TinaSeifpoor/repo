#ifndef COMMON_H
#define COMMON_H

typedef int ClassID;
typedef unsigned int FeatureIdx;
typedef double FeatureValue;

#include <QVariant>

struct TreeProperties
{
    double  baggingFactorFeatures,
            baggingFactorSamples;
    unsigned int maxDepth;
};

static const char* BaggingFactorFeaturesTree   ="BaggingFactorFeaturesTree";
static const char* BaggingFactorSamplesTree    ="BaggingFactorSamplesTree";
static const char* ForestSize                  ="ForestSize";
static const char* BaggingFactorFeaturesNode   ="BaggingFactorFeaturesNode";
static const char* BaggingFactorSamplesNode    ="BaggingFactorSamplesNode";
static const char* MaxDepth                    ="MaxDepth";

struct ForestProperties
{
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

    unsigned int    nTrees;
    double          baggingFactorFeatures,
                    baggingFactorSamples;
    TreeProperties  treeProperties;
};

struct Sample {
    QVariant sampleSource;
    ClassID sampleClass;
    QHash<FeatureIdx, FeatureValue> featureValues;
};

#endif // COMMON_H
