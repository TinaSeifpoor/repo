#include "MyDecisionForest.h"
#include <math.h>
#include <QtCore/qmath.h>
#include <algorithm>

void MyDecisionForest::readForest(QString forestText)
{
    QStringList treeText = forestText.split("\n", QString::SkipEmptyParts);
    MyForest forest;
    forest.clear();
    acd.clear();
    QStringList forestModelText   = treeText.takeFirst().split("\t", QString::SkipEmptyParts);
    this->forestModel.nFeatures   = forestModelText[0].toInt();
    this->forestModel.nClasses    = forestModelText[1].toInt();
    this->forestModel.patchWidth  = forestModelText[2].toInt();
    this->forestModel.patchHeight = forestModelText[3].toInt();
    QStringList patchOffsetsRowText = forestModelText[4].split(",");
    QStringList patchOffsetsColText = forestModelText[5].split(",");
    if (patchOffsetsRowText.count() != patchOffsetsColText.count())
    {
        qDebug("Forest model corrupted!");
        return;
    }
    for (int idxPatchOffset=0; idxPatchOffset<patchOffsetsRowText.count(); ++idxPatchOffset)
    {
        this->forestModel.patchOffsetsRows << patchOffsetsRowText[idxPatchOffset].toInt();
        this->forestModel.patchOffsetsCols << patchOffsetsColText[idxPatchOffset].toInt();
    }
    this->forestModel.maxOffsetRow = forestModelText[6].toInt();
    this->forestModel.maxOffsetCol = forestModelText[7].toInt();
    this->forestModel.BBWidth = forestModelText[8].toInt();
    this->forestModel.BBHeight = forestModelText[9].toInt();
    for (int idxTree=0; idxTree<treeText.count(); ++idxTree)
    {
        QString tree = treeText[idxTree];
        forest << this->readTree(tree);
        QVector<QVector<Label> > cdTree;
        for (int idxNode=0; idxNode<forest.last().count(); ++idxNode)
            cdTree << forest.last().at(idxNode).classDistributions;
        acd << cdTree;
    }
    this->forest= forest;
}

void MyDecisionForest::trainSample(QString sampleText)
{
    QStringList featVecText = sampleText.split("\t", QString::SkipEmptyParts);
    Label label = featVecText.first().toInt()-1;
    FeatureVec featVec;
    featVec.clear();
    for (int f=0; f<featVecText.count(); ++f)
        featVec << featVecText.at(f).toDouble();
    populateForest(featVec, label);
}

void MyDecisionForest::trainSampleMat(FeatureMat featMat)
{
    for (int f=0; f<featMat.count(); ++f)
    {
        FeatureVec featVec = featMat.at(f);
        Label label = featVec.at(0);
        featVec.remove(0);
        populateForest(featVec,label);
//        qDebug(QString("Training sample %1").arg(QString::number(f)).toAscii().constData());
    }
}

QString MyDecisionForest::dumpForest()
{
    QString forestText;
    foreach (MyTree tree, this->forest)
    {
        foreach (MyNode node, tree)
        {
            QString nodeText = QString("%1,%2,%3,").arg(QString::number(node.F1)).arg(QString::number(node.F2)).arg(QString::number(node.th));
            for (int idxClass=0; idxClass<node.classDistributions.count(); ++idxClass)
                nodeText.append(QString("%1,").arg(QString::number(node.classDistributions.at(idxClass))));
            nodeText.chop(1);
            forestText.append(QString("%1\t").arg(nodeText));
        }
        forestText.append("\n");
    }
    return forestText;
}

QVector<Label> MyDecisionForest::testSampleMat(FeatureMat featMat)
{
    QVector<Label> labelList;
    for (int f=0; f< featMat.size(); ++f)
    {
        FeatureVec featVec = featMat.at(f);
        featVec.erase(featVec.begin());
//        qDebug(QString("Testing sample %1").arg(QString::number(f)).toAscii().constData());
        labelList << testForest(featVec);
    }
    return labelList;
}

QVector<ClassDistribution> MyDecisionForest::testSampleMatCC(FeatureMat featMat)
{
    QVector<ClassDistribution> cc;
    for (int f=0; f< featMat.size(); ++f)
    {
        featVec = featMat.at(f);
        featVec.erase(featVec.begin());
        testForestCC();
//        qDebug(QString("Testing sample %1").arg(QString::number(f)).toAscii().constData());
        cc << this->cc;
    }
    return cc;
}

double MyDecisionForest::testSampleMatPerf(FeatureMat featMat)
{
    QList<int> resList;
    resList.clear();
    for (int f=0; f<featMat.count(); ++f)
    {
        FeatureVec featVec = featMat.at(f);
        Label label = featVec.at(0);
        featVec.remove(0);
        if (testForest(featVec) == label)
            resList<<1;
        else
            resList<<0;
//        qDebug(QString("Testing sample %1").arg(QString::number(f)).toAscii().constData());
    }
    double prob=0;
    while(!resList.isEmpty())
        prob+=resList.takeFirst();
    prob=prob/featMat.count();
    return prob;
}

MyTree MyDecisionForest::readTree(QString treeText)
{
    MyTree tree;
    tree.clear();
    QStringList nodesText = treeText.split("\t", QString::SkipEmptyParts);
    for (int n=0; n<nodesText.count(); ++n)
        tree << this->readNode(nodesText.at(n));
    return tree;
}

MyNode MyDecisionForest::readNode(QString nodeText)
{
    QStringList params = nodeText.split(",");
    if (params.count()<3)
    {
        qDebug(nodeText.toAscii().constData());
        return MyNode();
    }
    MyNode node;
    node.F1 = params.takeFirst().toInt();
    node.F2 = params.takeFirst().toInt();
    node.th = params.takeFirst().toDouble();
    node.classDistributions.resize(17);
    for (int i=0; !params.isEmpty(); ++i)
        node.classDistributions[i] = params.takeFirst().toInt();
    return node;
}

void MyDecisionForest::populateForest(FeatureVec featVec, Label l)
{
    for (int idxTree=0; idxTree < this->forest.count(); ++idxTree)
    {
        addSampleToTree(featVec, l, idxTree);
    }
}

void MyDecisionForest::testForestCC()
{
//    qDebug(QString("There are %1 trees.").arg(QString::number(this->forest.count())).toAscii().constData());
//    this->t.start();
    cc.clear();
    cc.resize(17);
    //ClassDistribution cc = testSampleAtTree(featVec, 0);
//    t1 = this->t.elapsed();
    int forestCount = forest.count();
    for (int idxTree=1; idxTree<forestCount; ++idxTree)
    {
        testSampleAtTreeCC(idxTree);
    }

    return;
}

Label MyDecisionForest::testForest(FeatureVec featVec)
{
//    qDebug(QString("There are %1 trees.").arg(QString::number(this->forest.count())).toAscii().constData());
    ClassDistribution cc = testSampleAtTree(featVec, 0);
    for (int idxTree=1; idxTree<this->forest.count(); ++idxTree)
    {
        ClassDistribution ccCurr = testSampleAtTree(featVec, idxTree);
        while (ccCurr.count()>cc.count())
            cc << 0;
        for (Label l=0; l<ccCurr.count(); ++l)
            cc[l]+=ccCurr.at(l);
    }

    int bestCount=0;
    Label bestClass=0;
    for (Label l=0; l<cc.count(); ++l)
    {
        if (cc.at(l)>bestCount)
        {
            bestCount = cc.at(l);
            bestClass = l;
        }
    }

    return bestClass;
}

void MyDecisionForest::addSampleToTree(FeatureVec featVec, Label l, int idxTree, int idxNode)
{
    if (this->forest.at(idxTree).isEmpty())
    {
        qDebug("What the fuck man ?");
        return;
    }
    if (idxNode > this->forest.at(idxTree).count())
    {
        idxNode = qFloor(double(idxNode)/2);
        while (this->forest.at(idxTree).at(idxNode-1).classDistributions.count() <= l)
            this->forest[idxTree][idxNode-1].classDistributions << 0;
        ++this->forest[idxTree][idxNode-1].classDistributions[l];
        return;
    }

    if (this->forest[idxTree][idxNode-1].F1==-1)
    {
        while (this->forest[idxTree][idxNode-1].classDistributions.count() <= l)
            this->forest[idxTree][idxNode-1].classDistributions << 0;
        ++this->forest[idxTree][idxNode-1].classDistributions[l];
        return;
    }

//    Feature F1 = featVec.at(this->forest.at(idxTree).at(idxNode-1).F1);
//    Feature F2 = featVec.at(this->forest.at(idxTree).at(idxNode-1).F2);
//    Feature feat = featVec.at(this->forest.at(idxTree).at(idxNode-1).F1)-featVec.at(this->forest.at(idxTree).at(idxNode-1).F2);

    bool isRight = featVec.at(this->forest.at(idxTree).at(idxNode-1).F1)-featVec.at(this->forest.at(idxTree).at(idxNode-1).F2)<this->forest.at(idxTree).at(idxNode-1).th;
    idxNode=idxNode*2;
    if (isRight)
        idxNode++;

    this->addSampleToTree(featVec, l, idxTree, idxNode);
    return;
}

ClassDistribution MyDecisionForest::testSampleAtTree(FeatureVec featVec, int idxTree, int idxNode)
{
    if (this->forest.at(idxTree).isEmpty())
        return ClassDistribution();
    if (this->forest.at(idxTree).count()<= idxNode)
    {
        idxNode = qFloor(idxNode/2);
        return this->acd.at(idxTree).at(idxNode-1);
//        return this->forest.at(idxTree).at(idxNode-1).classDistributions;
    }
    if (this->forest.at(idxTree).at(idxNode-1).F1==-1)
    {
        return this->acd.at(idxTree).at(idxNode-1);
//        return this->forest.at(idxTree).at(idxNode-1).classDistributions;
    }
//    Feature F1 = featVec[this->forest[idxTree][idxNode-1].F1];
//    Feature F2 = featVec[this->forest[idxTree][idxNode-1].F2];
//    Feature feat = F1-F2;
    bool isRight = featVec.at(this->forest.at(idxTree).at(idxNode-1).F1)-featVec.at(this->forest.at(idxTree).at(idxNode-1).F2)<this->forest.at(idxTree).at(idxNode-1).th;
    idxNode=idxNode*2;
    if (isRight)
        idxNode++;

    return this->testSampleAtTree(featVec, idxTree, idxNode);
}

void MyDecisionForest::testSampleAtTreeCC(int idxTree, int idxNode)
{
    if (this->forest.at(idxTree).isEmpty())
        return;
    if (this->forest.at(idxTree).count()<= idxNode)
    {
        idxNode = qFloor(idxNode/2);
        std::transform (cc.begin(), cc.end(), this->acd.at(idxTree).at(idxNode-1).begin(), cc.begin(), std::plus<float>());
        return;
//        return this->forest.at(idxTree).at(idxNode-1).classDistributions;
    }
    if (this->forest.at(idxTree).at(idxNode-1).F1==-1)
    {
        std::transform (cc.begin(), cc.end(), this->acd.at(idxTree).at(idxNode-1).begin(), cc.begin(), std::plus<float>());
        return;
//        return this->forest.at(idxTree).at(idxNode-1).classDistributions;
    }
//    Feature F1 = featVec[this->forest[idxTree][idxNode-1].F1];
//    Feature F2 = featVec[this->forest[idxTree][idxNode-1].F2];
//    Feature feat = F1-F2;
    bool isRight = featVec.at(this->forest.at(idxTree).at(idxNode-1).F1)-featVec.at(this->forest.at(idxTree).at(idxNode-1).F2)<this->forest.at(idxTree).at(idxNode-1).th;
    idxNode=idxNode*2;
    if (isRight)
        idxNode++;

    this->testSampleAtTreeCC(idxTree, idxNode);
    return;
}

