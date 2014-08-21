#include "node.h"
#include "math.h"
#include "vectorindexsorter.h"
#include "features.h"
#include "source.h"
//QVector<double> log2LookUpTable;
const int tableLength = 1000000;
const double log2 = 1.44269504088896340736;
double entropy(std::vector<unsigned int> sampleHistogram, unsigned int nSamples);

struct NodePrivate {
    // inputs
    const Source* source;
    const Features* features;
    TreeProperties properties;

    // outputs / postprocess
    Source* sourceLeft;
    Source* sourceRight;
    unsigned int featureIdx;
    double splitValue;
};



Node::Node(const Source *source, const Features *features, TreeProperties properties, Source *left, Source *right, double splitValue, unsigned int featureIdx):
    d(new NodePrivate)
{
    d->source = source;
    d->features = features;
    d->properties = properties;
    d->sourceLeft = left;
    d->sourceRight = right;
    d->splitValue = splitValue;
    d->featureIdx = featureIdx;
}

Node *Node::train(const Source *source, const Features* features, const TreeProperties properties)
{
//    if (log2LookUpTable.isEmpty()) {
//        for (int i=1; i<tableLength; ++i) {
//            log2LookUpTable << (log((long double)i/(long double)tableLength)/log2);
//        }
//        log2LookUpTable[0]=0;
//    }
    Source* samplesForNode = source->baggedSamples(properties.baggingFactorSamples);
    Features* featuresForNode = features->randomlySortedList(properties.baggingFactorFeatures);
    QList<ClassID> sampleClasses = samplesForNode->getSampleClasses();
    QHash<unsigned int, ClassID> uniqueClasses = samplesForNode->uniqueClasses();
    unsigned int nClasses = samplesForNode->countClasses();
    featuresForNode->setSource(samplesForNode);


    EntropyValue bestInformationGain = -INT_MAX;

    unsigned int bestFeatureIdx = -1;
    unsigned int nFeatures = featuresForNode->range();
    unsigned int nSamples = sampleClasses.size();
    double bestFeatureVal;
    std::vector<unsigned int>   sampleClassesHistogram;
            sampleClassesHistogram .resize(nClasses,0);
    for(int idx=0; idx<sampleClasses.size(); idx++) {
        ++sampleClassesHistogram[uniqueClasses.key(sampleClasses.at(idx))];
    }
    EntropyValue parent = entropy(sampleClassesHistogram, nSamples);
    for (unsigned int idxFeature=0; idxFeature<nFeatures; ++idxFeature) {
        std::vector<FeatureValue> featureValues = featuresForNode->getFeatureValues(idxFeature);// as big as sample count
        std::vector<unsigned int> sortIdx = sort_indexes(featureValues);

        for (unsigned int idxCurrent=1;idxCurrent<sortIdx.size();++idxCurrent) {
            std::vector<unsigned int>   sampleClassesHistogramLeft,
                                        sampleClassesHistogramRight;
            sampleClassesHistogramLeft .resize(nClasses,0);
            sampleClassesHistogramRight.resize(nClasses,0);

            for(unsigned int idxBeforeCurrent=0; idxBeforeCurrent<idxCurrent; idxBeforeCurrent++) {
                ++sampleClassesHistogramLeft[uniqueClasses.key(sampleClasses.at(sortIdx.at(idxBeforeCurrent)))];
            }
            for(unsigned int idxAfterCurrent=idxCurrent; idxAfterCurrent<sortIdx.size(); idxAfterCurrent++) {
                ++sampleClassesHistogramRight[uniqueClasses.key(sampleClasses.at(sortIdx.at(idxAfterCurrent)))];
            }
            EntropyValue    entropyLeftValue  = entropy(sampleClassesHistogramLeft ,nSamples),
                            entropyRightValue = entropy(sampleClassesHistogramRight,nSamples),
                            informationGain = parent - 0.5*entropyLeftValue - 0.5*entropyRightValue;

            if (informationGain > bestInformationGain) {
                bestInformationGain = informationGain;
                bestFeatureIdx = idxFeature;
                bestFeatureVal = (double)(samplesForNode->at(sortIdx.at(idxCurrent-1))->featureValues[bestFeatureIdx]+samplesForNode->at(sortIdx.at(idxCurrent))->featureValues[bestFeatureIdx])/2;
            }
        }
    }

    //

    Features* featuresForSplit = features->randomlySortedList(1);
    featuresForSplit->setSource(source);
    std::vector<double> featureValues = featuresForSplit->getFeatureValues(bestFeatureIdx);

    QList<Sample> samplesLeft, samplesRight;
    for (unsigned int idxSample=0; idxSample<source->countSamples(); idxSample++) {
        if (featureValues.at(idxSample)<bestFeatureVal)
            samplesLeft.append(*source->at(idxSample));
        else
            samplesRight.append(*source->at(idxSample));
    }
    return new Node(source, features, properties, new Source(samplesLeft), new Source(samplesRight), bestFeatureVal, bestFeatureIdx);
}

Node *Node::trainLeft(Node *parent)
{
    return Node::train(parent->leftSamples(), parent->features(), parent->treeProperties());
}

Node *Node::trainRight(Node *parent)
{
    return Node::train(parent->rightSamples(), parent->features(), parent->treeProperties());
}

const Features *Node::features() const
{
    return d->features;
}

TreeProperties Node::treeProperties() const
{
    return d->properties;
}

const Source *Node::leftSamples() const
{
    return d->sourceLeft;
}

const Source *Node::rightSamples() const
{
    return d->sourceRight;
}

double entropy(std::vector<unsigned int> sampleHistogram, unsigned int nSamples){
    int totalClasses = sampleHistogram.size();
    long double totalEntropy=0;
    for (int i=0; i<totalClasses; ++i) {
        long double prob = ((double)sampleHistogram.at(i)/(double)nSamples);
//        totalEntropy -= prob*log2LookUpTable.at(prob*tableLength);
        if (prob>0)
            totalEntropy -= prob*log(prob)/log2;
    }
    return totalEntropy;
}
