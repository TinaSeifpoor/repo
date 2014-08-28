#include "node.h"
#include "math.h"
#include "vectorindexsorter.h"
#include "features.h"
#include "source.h"
#include <QStringList>
#include <QStringBuilder>
const QString nodeText("<"%(QString)NodeText%" %1>\r\n\t\t\t<"%EntropyText%">%2</"%EntropyText%
                       ">\r\n\t\t\t<"%LeftUniqueClassesText %">%3</"%LeftUniqueClassesText %">\r\n\t\t\t<"%LeftSampleClassesText %">%4</"%LeftSampleClassesText %
                       ">\r\n\t\t\t<"%RightUniqueClassesText%">%5</"%RightUniqueClassesText%">\r\n\t\t\t<"%RightSampleClassesText%">%6</"%RightSampleClassesText%
                       ">\r\n\t\t\t<"%FeatureIdxText%">%7</"%FeatureIdxText%">\r\n\t\t\t<"%SplitValueText%">%8</"%SplitValueText%">\r\n\t\t</"%NodeText%">");
const int tableLength = 1000000;
const double log2 = 0.693147181;
double entropy(std::vector<int> sampleHistogram, int nSamples);


int depthFromLinearIdx(int linearIdx) {
    return floor(log((double)linearIdx+1)/log2+0.01)+1;
}

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

    QList<ClassID> leftUniqueClasses;
    QList<ClassID> rightUniqueClasses;
    QHash<QString, ClassID> leftSampleClasses;
    QHash<QString, ClassID> rightSampleClasses;

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
QString fromClassHash(QHash<QString, ClassID> hash) {
    QStringList out;
    foreach (QString sampleId, hash.keys())
        out << sampleId.append(QString(";%1").arg(hash.value(sampleId)));
    return out.join(",");
}

QString Node::text() const
{
    QStringList nodeTexts;
    nodeTexts << nodeText.arg(d->linearIdx).arg(d->parentEntropy)
                 .arg(fromClassList(d->leftUniqueClasses))
                 .arg(fromClassHash(d->leftSampleClasses))
                 .arg(fromClassList(d->rightUniqueClasses))
                 .arg(fromClassHash(d->rightSampleClasses))
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
    QList<ClassID> leftUniqueClasses;
    {
        QString beginText = LeftUniqueClassesText;
        beginText.prepend("<");
        beginText.append(">");
        QString endText = LeftUniqueClassesText;
        endText.append(">");
        endText.prepend("</");
        int beginInd = text.indexOf(beginText);
        int endInd = text.indexOf(endText);
        QString propertyValue = text.mid(beginInd+beginText.length(), endInd-beginInd-beginText.length());
        QStringList values = propertyValue.split(",");
        foreach (QString value, values)
            leftUniqueClasses << value.toInt();
    }
    QList<ClassID> rightUniqueClasses;
    {
        QString beginText = RightUniqueClassesText;
        beginText.prepend("<");
        beginText.append(">");
        QString endText = RightUniqueClassesText;
        endText.append(">");
        endText.prepend("</");
        int beginInd = text.indexOf(beginText);
        int endInd = text.indexOf(endText);
        QString propertyValue = text.mid(beginInd+beginText.length(), endInd-beginInd-beginText.length());
        QStringList values = propertyValue.split(",");
        foreach (QString value, values)
            rightUniqueClasses << value.toInt();
    }
    QHash<QString,ClassID> leftSampleClasses;
    {
        QString beginText = LeftSampleClassesText;
        beginText.prepend("<");
        beginText.append(">");
        QString endText = LeftSampleClassesText;
        endText.append(">");
        endText.prepend("</");
        int beginInd = text.indexOf(beginText);
        int endInd = text.indexOf(endText);
        QString propertyValue = text.mid(beginInd+beginText.length(), endInd-beginInd-beginText.length());
        QStringList values = propertyValue.split(",");
        foreach (QString value, values) {
            QStringList sampleIdAndClass = value.split(";",QString::SkipEmptyParts);
            if (sampleIdAndClass.count() == 2)
                leftSampleClasses.insert(sampleIdAndClass.at(0),sampleIdAndClass.at(1).toInt());
            else
                qWarning("nodeFromText(): Invalid value for sample classes: "+value.toLatin1());
        }
    }
    QHash<QString,ClassID> rightSampleClasses;
    {
        QString beginText = RightSampleClassesText;
        beginText.prepend("<");
        beginText.append(">");
        QString endText = RightSampleClassesText;
        endText.append(">");
        endText.prepend("</");
        int beginInd = text.indexOf(beginText);
        int endInd = text.indexOf(endText);
        QString propertyValue = text.mid(beginInd+beginText.length(), endInd-beginInd-beginText.length());
        QStringList values = propertyValue.split(",");
        foreach (QString value, values) {
            QStringList sampleIdAndClass = value.split(";",QString::SkipEmptyParts);
            if (sampleIdAndClass.count() == 2)
                rightSampleClasses.insert(sampleIdAndClass.at(0),sampleIdAndClass.at(1).toInt());
            else
                qWarning("nodeFromText(): Invalid value for sample classes: "+value.toLatin1());
        }
    }

    return new Node(linearIdx, pro, splitValue, featureIdx, entropy, leftUniqueClasses, leftSampleClasses, rightUniqueClasses, rightSampleClasses);
}

void Node::testSource(const Source *source, const Features* features, TestResult* result) const
{
    // need a copy
    Features* featuresForNode = features->baggedFeatures(1);
    featuresForNode->setSource(source);
    delete featuresForNode;
    for (int i=0; i<source->countSamples(); ++i) {
        Sample* sample = source->at(i);
        testSample(sample,features,result);
    }
}

void Node::testSample(const Sample *sample, const Features *features, TestResult* result) const
{
    // need a copy
    Features* featuresForNode = features->baggedFeatures(1);
    QList<Sample> sampleList;
    sampleList.append(*sample);
    Source* source = new Source(sampleList);
    featuresForNode->setSource(source);
    delete featuresForNode;
    double featureVal = sample->featureValues.value(d->featureIdx);
    bool isLeft = featureVal < d->splitValue;
    if (isLeft) {
        if(d->left) {
            return d->left->testSample(sample, features, result);
        } else {
            result->add(sample->sampleId, depthFromLinearIdx(d->linearIdx), d->leftSampleClasses);
        }
    } else {
        if(d->right) {
            return d->right->testSample(sample, features, result);
        } else {
            result->add(sample->sampleId, depthFromLinearIdx(d->linearIdx), d->rightSampleClasses);
        }
    }
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
    d->leftSampleClasses = left->getSampleID();
    d->leftUniqueClasses = left->uniqueClasses().values();
    d->rightSampleClasses = right->getSampleID();
    d->rightUniqueClasses = right->uniqueClasses().values();

}

Node::Node(const int linearIdx, TreeProperties properties, double splitValue, int featureIdx,
           double parentEntropy, QList<ClassID> leftUniqueClasses, QHash<QString, ClassID> leftSampleClasses,
           QList<ClassID> rightUniqueClasses, QHash<QString, ClassID> rightSampleClasses):
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
    d->leftUniqueClasses = leftUniqueClasses;
    d->leftSampleClasses = leftSampleClasses;
    d->rightUniqueClasses = rightUniqueClasses;
    d->rightSampleClasses = rightSampleClasses;
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
    int depth = depthFromLinearIdx(current->d->linearIdx);
    if (depth<properties.maxDepth) {
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
