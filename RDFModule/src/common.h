#ifndef COMMON_H
#define COMMON_H

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

#endif // COMMON_H
