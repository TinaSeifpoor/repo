#include "common.h"



void ForestProperties::set(QString var, QString val) {
    if (var == BaggingFactorFeaturesTree)
        baggingFactorFeatures=val.toDouble();
    if (var == BaggingFactorSamplesTree)
        baggingFactorSamples=val.toDouble();
    if (var == ForestSize)
        nTrees=val.toInt();
    if (var == MaxDepth)
        treeProperties.maxDepth=val.toInt();
    if (var == BaggingFactorFeaturesNode)
        treeProperties.baggingFactorFeatures=val.toDouble();
    if (var == BaggingFactorSamplesNode)
        treeProperties.baggingFactorSamples=val.toDouble();
}

void ForestProperties::setAll(QString text) {
    QStringList forestPropertiesKeywords = QStringList()    << BaggingFactorFeaturesTree
                                                            << BaggingFactorFeaturesTree
                                                            << BaggingFactorSamplesTree
                                                            << ForestSize
                                                            << BaggingFactorFeaturesNode
                                                            << BaggingFactorSamplesNode
                                                            << MaxDepth;
    foreach (QString forestPropertiesKeyword, forestPropertiesKeywords) {
        QString beginText = forestPropertiesKeyword;
        beginText.prepend("<");
        beginText.append(">");
        QString endText = forestPropertiesKeyword;
        endText.append(">");
        endText.prepend("</");
        int beginInd = text.indexOf(beginText);
        int endInd = text.indexOf(endText);
        QString propertyValue = text.mid(beginInd+beginText.length(), endInd-beginInd-beginText.length());
        set(forestPropertiesKeyword,propertyValue);
    }
}

template<typename T>
QPair<QList<int>, QList<T> > getSampleHistogram(QList<T> list){
    QList<int> histogram;
    QList<T> uniqueList;
    foreach (T item, list) {
        if (!uniqueList.contains(item)) {
            uniqueList.append(item);
            histogram.append(1);
        } else {
            int idx = uniqueList.indexOf(item);
            histogram[idx]++;
        }
    }
    return qMakePair<QList<int>, QList<T>>(histogram, uniqueList);
}


void TestResult::setTreeIndex(int treeIdx) {
    this->treeIdx = treeIdx;
}

void TestResult::add(QString testSampleId, int nodeDepth, QHash<QString, ClassID> trainSampleIDHash) {
    TreeResult t;
    t.treeDepth = nodeDepth;
    t.trainSampleIDHash = trainSampleIDHash;
    t.treeIdx = treeIdx;
    container.insertMulti(testSampleId,t);
}

ClassID TestResult::getSampleClassMajority(QString sampleID) {
    QList<TreeResult> treeResults = container.values(sampleID);
    QList<ClassID> classList;
    foreach (TreeResult result, treeResults) {
        classList+=result.trainSampleIDHash.values();
    }
    QPair<QList<ClassID>,QList<int>> histogram = getSampleHistogram(classList);
    int maxCount = -1;
    ClassID classChosen;
    for (int i=0; i<histogram.second.count();++i) {
        if (histogram.second.at(i)>maxCount) {
            maxCount = histogram.first.at(i);
            classChosen = histogram.second.at(i);
        }
    }
    return classChosen;
}
