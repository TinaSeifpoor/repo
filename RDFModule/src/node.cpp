#include "node.h"
#include "math.h"
const int tableLength = 1000000;
static QVector<double> log2LookUpTable;

template <typename T>
std::vector<unsigned int> sort_indexes(const std::vector<T> &v) {

  // initialize original index locations
  std::vector<unsigned int> idx(v.size());
  for (unsigned int i = 0; i != idx.size(); ++i) idx[i] = i;

  // sort indexes based on comparing values in v
  std::sort(idx.begin(), idx.end(),
       [&v](unsigned int i1, unsigned int i2) {return v[i1] < v[i2];});

  return idx;
}

Node::Node()
{
    if (log2LookUpTable.isEmpty()) {
        for (int i=0; i<tableLength; ++i) {
            log2LookUpTable << (log((long double)i/(long double)tableLength)/log2);
        }
    }
}

void Node::train(const Source *samples, const TreeProperties properties, Source *samplesTrue, Source *samplesFalse)
{
    Source* samplesForNode = samples->baggedSamples(properties.baggingFactorSamples, properties.baggingFactorFeatures);
    EntropyValue bestEntropy = INT_MAX;
    FeatureValue bestFeatureValue;
    unsigned int bestFeatureIdx = -1;
    unsigned int nFeatures = samplesForNode->countFeatures();
    std::vector<ClassID> sampleClasses = samplesForNode->getSampleClasses();
    unsigned int nClasses = samplesForNode->countClasses();
    for (unsigned int idxFeature=0; idxFeature<nFeatures; ++idxFeature) {
        std::vector<FeatureValue> featureValues = samplesForNode->getFeatureValues(idxFeature); // as big as sample count
        std::vector<unsigned int> sortIdx = sort_indexes(featureValues);
        std::vector<unsigned int>::iterator sortIdxItBegin = sortIdx.begin();
        std::vector<unsigned int>::iterator sortIdxItEnd = sortIdx.end();
        std::vector<unsigned int>::iterator sortIdxIt = sortIdx.begin();
        std::vector<unsigned int>::iterator sortIdxItEndPop = sortIdxItEnd-1;
        for (;sortIdxIt!=sortIdxItEndPop;) {
            std::vector<ClassID> sampleClassesTrue, sampleClassesFalse;
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
            EntropyValue entropyValue = entropy(sampleClassesHistogram);
            if (entropyValue < bestEntropy) {
                bestEntropy = entropyValue;
                bestFeatureValue = featureValues.at(*sortIdxIt) + featureValues.at(*(++sortIdxIt));
                bestFeatureIdx = idxFeature;
            }
        }
    }
}

double Node::entropy(std::vector<unsigned int> sampleHistogram){
    int totalClasses = sampleHistogram.size();

    qreal totalEntropy=0;
    for (int i=0; i<totalClasses; ++i) {
        qreal prob = (sampleHistogram.at(i)/totalClasses);
        totalEntropy -= prob*log2LookUpTable.at(prob*tableLength);
    }
    return totalEntropy;
}
