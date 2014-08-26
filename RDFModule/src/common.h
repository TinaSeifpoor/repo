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

struct ForestProperties
{
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
