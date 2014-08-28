#include "node.h"
#include "math.h"
#include "vectorindexsorter.h"
#include "features.h"
#include "source.h"
#include <QStringList>
const QString nodeText("<Node %1>\r\n\t\t\t<Entropy>%2</Entropy>\r\n\t\t\t<UniqueClasses>%3</UniqueClasses>\r\n\t\t\t<Classes>%4</Classes>\r\n\t\t\t<FeatureIdx>%5</FeatureIdx>\r\n\t\t\t<SplitValue>%6</SplitValue>\r\n\t\t</Node>");
const int tableLength = 1000000;
const double log2 = 0.693147181;
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
    int featureIdx;
    double splitValue;
    double parentEntropy;
    double leftEntropy;
    double rightEntropy;
    double informationGain;
    int linearIdx;

    QList<ClassID> uniqueClasses;
    QList<ClassID> classes;

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
                 .arg(fromClassList(d->uniqueClasses))
                 .arg(fromClassList(d->classes))
                 .arg(d->featureIdx).arg(d->splitValue);
    if (d->left)
        nodeTexts << d->left->text();
    if (d->right)
        nodeTexts << d->right->text();
    return nodeTexts.join("\r\n\t\t");
}

Node *Node::treeFromText(QString text, TreeProperties pro)
{

    QHash<int,Node*> nodeHash;

    QString beginText = NodeText;
    beginText.prepend("<");
    QString endText = NodeText;
    endText.append(">");
    endText.prepend("</");

    int previousBeginInd = -1;
    int previousEndInd = -1;
    while (true) {
        int beginInd = text.indexOf(beginText, previousBeginInd+1);
        int endInd = text.indexOf(endText, previousEndInd+1);
        if (beginInd!=-1 && endInd!=-1) {
            Node* c =  Node::nodeFromText(text.mid(beginInd+beginText.length(), endInd-beginInd-beginText.length()), pro);
            nodeHash.insert(c->d->linearIdx,c);
        }
        else
            break;
        previousBeginInd = beginInd;
        previousEndInd = endInd;
    }

    QList<int> sortedNodeIdx = nodeHash.keys();
    qSort(sortedNodeIdx);
    for (int i=sortedNodeIdx.count()-1; i>0; --i) {
        Node* c = nodeHash.value(i);
        int idxParent = (i-1)/2;
        Node* p = nodeHash.value(idxParent);
        if (i%2) {
            // left
            p->d->left = c;
            p->d->leftEntropy = c->d->parentEntropy;
        } else {
            // right
            p->d->right = c;
            p->d->rightEntropy = c->d->parentEntropy;
        }
        nodeHash.remove(i);
    }
    return nodeHash.value(0);
}

Node *Node::nodeFromText(QString text, TreeProperties pro)
{
    int linearIdx;
    {
        int endInd = text.indexOf(">");
        QString propertyValue = text.left(endInd);
        linearIdx = propertyValue.toInt();
    }
    double entropy;
    {
        QString beginText = EntropyText;
        beginText.prepend("<");
        beginText.append(">");
        QString endText = EntropyText;
        endText.append(">");
        endText.prepend("</");
        int beginInd = text.indexOf(beginText);
        int endInd = text.indexOf(endText);
        QString propertyValue = text.mid(beginInd+beginText.length(), endInd-beginInd-beginText.length());
        entropy = propertyValue.toDouble();
    }
    int featureIdx;
    {
        QString beginText = FeatureIdxText;
        beginText.prepend("<");
        beginText.append(">");
        QString endText = FeatureIdxText;
        endText.append(">");
        endText.prepend("</");
        int beginInd = text.indexOf(beginText);
        int endInd = text.indexOf(endText);
        QString propertyValue = text.mid(beginInd+beginText.length(), endInd-beginInd-beginText.length());
        featureIdx = propertyValue.toDouble();
    }
    double splitValue;
    {
        QString beginText = SplitValueText;
        beginText.prepend("<");
        beginText.append(">");
        QString endText = SplitValueText;
        endText.append(">");
        endText.prepend("</");
        int beginInd = text.indexOf(beginText);
        int endInd = text.indexOf(endText);
        QString propertyValue = text.mid(beginInd+beginText.length(), endInd-beginInd-beginText.length());
        splitValue = propertyValue.toDouble();
    }
    QList<ClassID> uniqueClasses;
    {
        QString beginText = UniqueClassesText;
        beginText.prepend("<");
        beginText.append(">");
        QString endText = UniqueClassesText;
        endText.append(">");
        endText.prepend("</");
        int beginInd = text.indexOf(beginText);
        int endInd = text.indexOf(endText);
        QString propertyValue = text.mid(beginInd+beginText.length(), endInd-beginInd-beginText.length());
        QStringList values = propertyValue.split(",");
        foreach (QString value, values)
            uniqueClasses << value.toInt();
    }
    QList<ClassID> classes;
    {
        QString beginText = ClassesText;
        beginText.prepend("<");
        beginText.append(">");
        QString endText = ClassesText;
        endText.append(">");
        endText.prepend("</");
        int beginInd = text.indexOf(beginText);
        int endInd = text.indexOf(endText);
        QString propertyValue = text.mid(beginInd+beginText.length(), endInd-beginInd-beginText.length());
        QStringList values = propertyValue.split(",");
        foreach (QString value, values)
            classes << value.toInt();
    }

    return new Node(linearIdx, pro, splitValue, featureIdx, entropy, uniqueClasses, classes);
}

Node::~Node()
{
    delete d;
}


Node::Node(const int linearIdx, const Source *source, const Features *features,
           TreeProperties properties, Source *left, Source *right, double splitValue,
           int featureIdx, double parentEntropy, double leftEntropy,
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
    d->classes = source->getSampleClasses();
    d->uniqueClasses = source->uniqueClasses().values();
}

Node::Node(const int linearIdx, TreeProperties properties, double splitValue, int featureIdx,
           double parentEntropy, QList<ClassID> uniqueClasses, QList<ClassID> classes):
    d(new NodePrivate)
{
    d->linearIdx = linearIdx;
    d->m_properties = properties;
    d->splitValue = splitValue;
    d->featureIdx = featureIdx;
    d->parentEntropy = parentEntropy;
    d->right = 0;
    d->left = 0;
    d->leftEntropy = -1;
    d->rightEntropy = -1;
    d->m_source = 0;
    d->sourceLeft = 0;
    d->sourceRight = 0;
    d->informationGain = 0;
    d->uniqueClasses = uniqueClasses;
    d->classes = classes;
}

Node *Node::train(const Source *source, const Features* features, const TreeProperties properties, int linearIdx)
{
    Source* samplesForNode = source->baggedSamples(properties.baggingFactorSamples);
    Features* featuresForNode = features->baggedFeatures(properties.baggingFactorFeatures);
    QList<ClassID> sampleClasses = samplesForNode->getSampleClasses();
    QHash<int, ClassID> uniqueClasses = samplesForNode->uniqueClasses();
    int nClasses = samplesForNode->countClasses();
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

        for (int idxCurrent=1;idxCurrent<(int)sortIdx.size();++idxCurrent) {
            std::vector<int>   sampleClassesHistogramLeft,
                    sampleClassesHistogramRight;
            sampleClassesHistogramLeft .resize(nClasses,0);
            sampleClassesHistogramRight.resize(nClasses,0);

            for(int idxBeforeCurrent=0; idxBeforeCurrent<idxCurrent; idxBeforeCurrent++) {
                ++sampleClassesHistogramLeft[uniqueClasses.key(sampleClasses.at(sortIdx.at(idxBeforeCurrent)))];
            }
            for(int idxAfterCurrent=idxCurrent; idxAfterCurrent<(int)sortIdx.size(); idxAfterCurrent++) {
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
    for (int idxSample=0; idxSample<source->countSamples(); idxSample++) {
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
    double depth = log((double)linearIdx+1)/log2;
    if (depth<properties.maxDepth-1.1) {
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
