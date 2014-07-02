#ifndef COMMON_H
#define COMMON_H

typedef unsigned int ClassID;
typedef unsigned int FeatureIdx;
typedef double FeatureValue;

#include <QVariant>


enum SplittingCriterion
{
    InformationGain,
    GiniImpurity
};

struct TreeProperties
{
    double  baggingFactorFeatures,
            baggingFactorSamples;
    unsigned int maxDepth;
    SplittingCriterion criteria;
};

struct ForestProperties
{
    unsigned int    nTrees;
    double          baggingFactorFeatures,
                    baggingFactorSamples;
    TreeProperties treeProperties;
};

struct Sample {
    QVariant sampleSource;
    ClassID sampleClass;
    QHash<FeatureIdx, FeatureValue> featureValues;
};

#endif // COMMON_H
