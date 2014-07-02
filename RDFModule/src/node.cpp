#include "node.h"
#include "math.h"
#include "vectorindexsorter.h"
#include "features.h"
#include "source.h"
QVector<double> log2LookUpTable;
const int tableLength = 1000000;
const double log2 = 0.69314718055994530941723212145818;


Node::Node()
{
    if (log2LookUpTable.isEmpty()) {
        for (int i=1; i<tableLength; ++i) {
            log2LookUpTable << (log((long double)i/(long double)tableLength)/log2);
        }
        log2LookUpTable[0]=0;
    }
}

void Node::train(const Source *samples, const Features* features, const TreeProperties properties, Source *samplesTrue, Source *samplesFalse)
{
    Source* samplesForNode = samples->baggedSamples(properties.baggingFactorSamples);
    Features* featuresForNode = features->randomlySortedList(properties.baggingFactorFeatures);
    QList<ClassID> sampleClasses = samplesForNode->getSampleClasses();
    unsigned int nClasses = samplesForNode->countClasses();
    featuresForNode->setSource(samplesForNode);

    EntropyValue bestEntropy = INT_MAX;

    unsigned int bestFeatureIdx = -1;
    unsigned int nFeatures = featuresForNode->range();
    unsigned int nSamples = sampleClasses.size();
    std::vector<unsigned int>   sampleClassesHistogram;
            sampleClassesHistogram .resize(nClasses,0);
    for(int idxCurrent=0; idxCurrent<sampleClasses.size(); idxCurrent++) {
        ++sampleClassesHistogram[sampleClasses.at(idxCurrent)];
    }
    EntropyValue parent = entropy(sampleClassesHistogram, nSamples);
    for (unsigned int idxFeature=0; idxFeature<nFeatures; ++idxFeature) {
        std::vector<FeatureValue> featureValues = featuresForNode->getFeatureValues(idxFeature);// as big as sample count
        std::vector<unsigned int> sortIdx = sort_indexes(featureValues);



        for (int idxCurrent=1;idxCurrent<sortIdx.size();++idxCurrent) {
            std::vector<unsigned int>   sampleClassesHistogramLeft,
                                        sampleClassesHistogramRight;
            sampleClassesHistogramLeft .resize(nClasses,0);
            sampleClassesHistogramRight.resize(nClasses,0);

            for(int idxBeforeCurrent=0; idxBeforeCurrent<idxCurrent; idxBeforeCurrent++) {
                ++sampleClassesHistogramLeft[sampleClasses.at(sortIdx.at(idxBeforeCurrent))];
            }
            for(int idxAfterCurrent=idxCurrent; idxAfterCurrent<sortIdx.size(); idxAfterCurrent++) {
                ++sampleClassesHistogramRight[sampleClasses.at(sortIdx.at(idxAfterCurrent))];
            }
            EntropyValue    entropyLeftValue  = entropy(sampleClassesHistogramLeft ,nSamples),
                            entropyRightValue = entropy(sampleClassesHistogramRight,nSamples),
                            entropyValue = parent - 0.5*entropyLeftValue - 0.5*entropyRightValue;

            if (entropyValue < bestEntropy) {
                bestEntropy = entropyValue;
                bestFeatureIdx = idxFeature;
            }
        }
    }
    int i=5;
    ++i;
}

double Node::entropy(std::vector<unsigned int> sampleHistogram, unsigned int nSamples){
    int totalClasses = sampleHistogram.size();
    long double totalEntropy=0;
    for (int i=0; i<totalClasses; ++i) {
        long double prob = ((double)sampleHistogram.at(i)/(double)nSamples);
        totalEntropy -= prob*log2LookUpTable.at(prob*tableLength);
//        totalEntropy -= prob*log(prob)/log2;
    }
    return totalEntropy;
}
