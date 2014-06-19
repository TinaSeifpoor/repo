#include "node.h"
#include "math.h"
#include "vectorindexsorter.h"
QVector<double> log2LookUpTable;
const int tableLength = 1000000;



Node::Node()
{
    if (log2LookUpTable.isEmpty()) {
        for (int i=1; i<tableLength; ++i) {
            log2LookUpTable << (log((long double)i/(long double)tableLength)/log2);
        }
        log2LookUpTable[0]=0;
    }
}

void Node::train(const Source *samples, const TreeProperties properties, Source *samplesTrue, Source *samplesFalse)
{
    Source* samplesForNode = samples->baggedSamples(properties.baggingFactorSamples, properties.baggingFactorFeatures);
    EntropyValue bestEntropy = INT_MAX;
    FeatureValue bestFeatureValue;
    unsigned int bestFeatureIdx = -1;
    unsigned int nFeatures = samplesForNode->countFeatures();
    QList<ClassID> sampleClasses = samplesForNode->getSampleClasses();
    unsigned int nSamples = sampleClasses.size();
    unsigned int nClasses = samplesForNode->countClasses();
    for (unsigned int idxFeature=0; idxFeature<nFeatures; ++idxFeature) {

        std::vector<FeatureValue> featureValues = samplesForNode->getFeatureValues(idxFeature); // as big as sample count
        std::vector<unsigned int> sortIdx = sort_indexes(featureValues);


        std::vector<unsigned int>::iterator sortIdxItBegin = sortIdx.begin();
        std::vector<unsigned int>::iterator sortIdxItEnd = sortIdx.end();
        std::vector<unsigned int>::iterator sortIdxIt = sortIdx.begin();
        std::vector<unsigned int>::iterator sortIdxItEndPop = sortIdxItEnd-1;
        for (;sortIdxIt!=sortIdxItEndPop;) {
            QList<ClassID> sampleClassesTrue, sampleClassesFalse;
            std::vector<unsigned int>::iterator sortIdxItCurrent = sortIdxItBegin;
            std::vector<unsigned int> sampleClassesHistogram;
            sampleClassesHistogram.resize(nClasses,0);
            for(;sortIdxItCurrent!=sortIdxIt;++sortIdxItCurrent) {
                sampleClassesTrue.push_back(sampleClasses.at(*sortIdxItCurrent));
                ++sampleClassesHistogram[sampleClassesTrue.back()];
            }
            sampleClassesTrue.push_back(sampleClasses.at(*sortIdxItCurrent));
            ++sortIdxItCurrent;
            for(;sortIdxItCurrent!=sortIdxItEnd;++sortIdxItCurrent) {
                sampleClassesFalse.push_back(sampleClasses.at(*sortIdxItCurrent));
                ++sampleClassesHistogram[sampleClassesFalse.back()];
            }
            EntropyValue entropyValue = entropy(sampleClassesHistogram,nSamples);
            if (entropyValue < bestEntropy) {
                bestEntropy = entropyValue;
                bestFeatureValue = featureValues.at(*sortIdxIt) + featureValues.at(*(++sortIdxIt));
                bestFeatureIdx = idxFeature;
            }
        }
    }
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
