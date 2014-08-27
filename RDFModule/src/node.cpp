#include "node.h"
#include "math.h"
#include "vectorindexsorter.h"
#include "features.h"
#include "source.h"
#include <QStringList>
const QString nodeText("<Node %1>\r\n\t\t\t<Entropy>%2</Entropy>\r\n\t\t\t<UniqueClasses>%3</UniqueClasses>\r\n\t\t\t<Classes>%4</Classes>\r\n\t\t\t<FeatureIdx>%5</FeatureIdx>\r\n\t\t\t<SplitValue>%6</SplitValue>\r\n\t\t</Node>");
const int tableLength = 1000000;
const double log2 = 1.44269504088896340736;
double entropy(std::vector<int> sampleHistogram, int nSamples);


struct NodePrivate {
    void trainLeft();
    void trainRight();

    // inputs
    const Source* m_source;
    const Features* m_features;
    TreeProperties m_properties;

    // outputs / postprocess
    Source* sourceLeft;
    const Node* left;
    Source* sourceRight;
    const Node* right;
    unsigned int featureIdx;
    double splitValue;
    double parentEntropy;
    double leftEntropy;
    double rightEntropy;
    double informationGain;
    unsigned int linearIdx;

    //
    ~NodePrivate() {
        delete m_source;
        delete right;
        delete left;
    }
};

QString fromClassList(QList<ClassID> list) {
    QStringList out;
    for (int i=0; i<list.count(); ++i) {
        out << QString::number(list.at(i));
    }
    return out.join(",");
}

QString Node::text() const
{
    QStringList nodeTexts;
    nodeTexts << nodeText.arg(d->linearIdx).arg(d->parentEntropy)
                 .arg(fromClassList(d->m_source->uniqueClasses().values()))
                 .arg(fromClassList(d->m_source->getSampleClasses()))
                 .arg(d->featureIdx).arg(d->splitValue);
    if (d->left)
        nodeTexts << d->left->text();
    if (d->right)
        nodeTexts << d->right->text();
    return nodeTexts.join("\r\n\t\t");
}

Node::~Node()
{
    delete d;
}


Node::Node(const unsigned int linearIdx, const Source *source, const Features *features,
           TreeProperties properties, Source *left, Source *right, double splitValue,
           unsigned int featureIdx, double parentEntropy, double leftEntropy,
           double rightEntropy, double informationGain):
    d(new NodePrivate)
{
    d->m_source = source;
    d->m_features = features;
    d->m_properties = properties;
    d->sourceLeft = left;
    d->sourceRight = right;
    d->splitValue = splitValue;
    d->featureIdx = featureIdx;
    d->parentEntropy = parentEntropy;
    d->leftEntropy = leftEntropy;
    d->rightEntropy = rightEntropy;
    d->informationGain = informationGain;
    d->linearIdx = linearIdx;
    d->right = 0;
    d->left = 0;
}

Node *Node::train(const Source *source, const Features* features, const TreeProperties properties, unsigned int linearIdx)
{
    Source* samplesForNode = source->baggedSamples(properties.baggingFactorSamples);
    Features* featuresForNode = features->baggedFeatures(properties.baggingFactorFeatures);
    QList<ClassID> sampleClasses = samplesForNode->getSampleClasses();
    QHash<unsigned int, ClassID> uniqueClasses = samplesForNode->uniqueClasses();
    unsigned int nClasses = samplesForNode->countClasses();
    featuresForNode->setSource(samplesForNode);


    EntropyValue bestInformationGain = -INT_MAX;

    int bestFeatureIdx = -1;
    int nFeatures = featuresForNode->range();
    int nSamples = sampleClasses.size();
    std::vector<int> bestSortIdx;
    int bestCurrent;
    double bestFeatureVal;
    double bestLeftEntropy, bestRightEntropy;
    std::vector<int>   sampleClassesHistogram;
            sampleClassesHistogram .resize(nClasses,0);
    for(int idx=0; idx<sampleClasses.size(); idx++) {
        ++sampleClassesHistogram[uniqueClasses.key(sampleClasses.at(idx))];
    }
    EntropyValue parent = entropy(sampleClassesHistogram, nSamples);
    for (int idxFeature=0; idxFeature<nFeatures; ++idxFeature) {
        std::vector<FeatureValue> featureValues = featuresForNode->getFeatureValues(idxFeature);// as big as sample count
        std::vector<int> sortIdx = sort_indexes(featureValues);

        for (int idxCurrent=1;idxCurrent<sortIdx.size();++idxCurrent) {
            std::vector<int>   sampleClassesHistogramLeft,
                                        sampleClassesHistogramRight;
            sampleClassesHistogramLeft .resize(nClasses,0);
            sampleClassesHistogramRight.resize(nClasses,0);

            for(int idxBeforeCurrent=0; idxBeforeCurrent<idxCurrent; idxBeforeCurrent++) {
                ++sampleClassesHistogramLeft[uniqueClasses.key(sampleClasses.at(sortIdx.at(idxBeforeCurrent)))];
            }
            for(int idxAfterCurrent=idxCurrent; idxAfterCurrent<sortIdx.size(); idxAfterCurrent++) {
                ++sampleClassesHistogramRight[uniqueClasses.key(sampleClasses.at(sortIdx.at(idxAfterCurrent)))];
            }
            EntropyValue    entropyLeftValue  = entropy(sampleClassesHistogramLeft ,nSamples),
                            entropyRightValue = entropy(sampleClassesHistogramRight,nSamples),
                            informationGain = parent - 0.5*entropyLeftValue - 0.5*entropyRightValue;

            if (informationGain > bestInformationGain) {
                bestInformationGain = informationGain;
                bestFeatureIdx = idxFeature;
                bestLeftEntropy = entropyLeftValue;
                bestRightEntropy = entropyRightValue;
                bestSortIdx = sortIdx;
                bestCurrent = idxCurrent;
                double bestValLeft = samplesForNode->at(sortIdx.at(idxCurrent-1))->featureValues[bestFeatureIdx];
                double bestValRight = samplesForNode->at(sortIdx.at(idxCurrent))->featureValues[bestFeatureIdx];
                bestFeatureVal = (bestValLeft+bestValRight)/2;
            }
        }
    }

    //

    Features* featuresForSplit = features->baggedFeatures(1);
    featuresForSplit->setSource(source);
    std::vector<double> featureValues = featuresForSplit->getFeatureValues(bestFeatureIdx);

    QList<Sample> samplesLeft, samplesRight;
    for (unsigned int idxSample=0; idxSample<source->countSamples(); idxSample++) {
        if (featureValues.at(idxSample)>bestFeatureVal)
            samplesRight.append(*source->at(idxSample));
        else
            samplesLeft.append(*source->at(idxSample));
    }
    if (samplesRight.isEmpty()) {
        qDebug("Right empty");
    }
    if (samplesLeft.isEmpty()) {
        qDebug("Left empty");
    }
    Node* current = new Node(linearIdx, source, features, properties,
                        new Source(samplesLeft), new Source(samplesRight),
                        bestFeatureVal, bestFeatureIdx,
                        parent, bestLeftEntropy, bestRightEntropy, bestInformationGain);
    if (linearIdx/2<properties.maxDepth) {
        current->d->trainLeft();
        current->d->trainRight();
    }

    return current;
}


void NodePrivate::trainLeft()
{
    left = Node::train(sourceLeft, m_features, m_properties,linearIdx*2+1);
}

void NodePrivate::trainRight()
{
    right = Node::train(sourceRight, m_features, m_properties,linearIdx*2+2);
}

double entropy(std::vector<int> sampleHistogram, int nSamples){
    int totalClasses = sampleHistogram.size();
    long double totalEntropy=0;
    for (int i=0; i<totalClasses; ++i) {
        long double prob = ((double)sampleHistogram.at(i)/(double)nSamples);
        if (prob>0)
            totalEntropy -= prob*log(prob)/log2;
    }
    if (totalClasses==0)
        totalEntropy = INT_MAX;
    return totalEntropy;
}