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



#define log2 0.30102999566398119521373889472449

#endif // COMMON_H
