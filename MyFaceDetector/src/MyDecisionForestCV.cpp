//#include "MyDecisionForestCV.h"
//#include <math.h>
//#include <QtCore/qmath.h>
//MyDecisionForestCV::MyDecisionForestCV()
//{
//}

//void MyDecisionForestCV::readForest(QString forestText)
//{
//    QStringList treeText = forestText.split("\n", QString::SkipEmptyParts);
//    MyForest forest;
//    forest.clear();
//    foreach (QString tree, treeText)
//        forest << this->readTree(tree);
//    this->forest= forest;
//}

//void MyDecisionForestCV::trainSample(QString sampleText)
//{
//    QStringList featVecText = sampleText.split("\t", QString::SkipEmptyParts);
//    Label label = featVecText.first().toInt()-1;
//    FeatureVec featVec(1547,1,CV_32F);
//    for (int f=0; f<featVecText.count(); ++f)
//        featVec.at<float>(f,0)= featVecText[f].toDouble();
//    populateForest(featVec, label);
//}

//void MyDecisionForestCV::trainSampleMat(FeatureMat featMat)
//{
//    for (int f=0; f<featMat.rows; ++f)
//    {
//        FeatureVec featVec = featMat(cv::Rect(f, 1, f, featMat.cols-1));
//        Label label = featMat.at<float>(f,0);
//        populateForest(featVec,label);
////        qDebug(QString("Training sample %1").arg(QString::number(f)).toAscii().constData());
//    }
//}

//QString MyDecisionForestCV::dumpForest()
//{
//    QString forestText;
//    foreach (MyTree tree, this->forest)
//    {
//        foreach (MyNode node, tree)
//        {
//            QString nodeText = QString("%1,%2,%3,").arg(QString::number(node.F1)).arg(QString::number(node.F2)).arg(QString::number(node.th));
//            for (int idxClass=0; idxClass<node.classDistributions.cols; ++idxClass)
//                nodeText.append(QString("%1,").arg(QString::number(node.classDistributions.at<uchar>(0,idxClass))));
//            nodeText.chop(1);
//            forestText.append(QString("%1\t").arg(nodeText));
//        }
//        forestText.append("\n");
//    }
//    return forestText;
//}

//QList<Label> MyDecisionForestCV::testSampleMat(FeatureMat featMat)
//{
//    QList<Label> labelList;
//    for (int f=0; f< featMat.rows; ++f)
//    {
//        FeatureVec featVec = featMat(cv::Rect(f, 1, f, featMat.cols-1));
//        labelList << testForest(featVec);
//    }
//    return labelList;
//}

//QList<ClassCounts> MyDecisionForestCV::testSampleMatCC(FeatureMat featMat)
//{
//    QList<ClassCounts> cc;
//    for (int f=0; f< featMat.rows; ++f)
//    {
//        FeatureVec featVec = featMat(cv::Rect(f, 1, f, featMat.cols-1));
//        cc << testForestCC(featVec);
//    }
//    return cc;
//}

//double MyDecisionForestCV::testSampleMatPerf(FeatureMat featMat)
//{
//    QList<int> resList;
//    resList.clear();
//    for (int f=0; f<featMat.rows; ++f)
//    {
//        FeatureVec featVec = featMat(cv::Rect(f, 1, f, featMat.cols-1));
//        Label label = featMat.at<float>(f,0);
//        if (testForest(featVec) == label)
//            resList<<1;
//        else
//            resList<<0;
////        qDebug(QString("Testing sample %1").arg(QString::number(f)).toAscii().constData());
//    }
//    double prob=0;
//    while(!resList.isEmpty())
//        prob+=resList.takeFirst();
//    prob=prob/featMat.rows;
//    return prob;
//}

//MyTree MyDecisionForestCV::readTree(QString treeText)
//{
//    MyTree tree;
//    tree.clear();
//    QStringList nodesText = treeText.split("\t", QString::SkipEmptyParts);
//    for (int n=0; n<nodesText.count(); ++n)
//        tree << this->readNode(nodesText[n]);
//    return tree;
//}

//MyNode MyDecisionForestCV::readNode(QString nodeText)
//{
//    QStringList params = nodeText.split(",", QString::SkipEmptyParts);
//    if (params.count()<3)
//    {
//        qDebug(nodeText.toAscii().constData());
//        return MyNode();
//    }
//    MyNode node;
//    node.F1 = params.takeFirst().toInt();
//    node.F2 = params.takeFirst().toInt();
//    node.th = params.takeFirst().toDouble();
//    node.classDistributions = cv::Mat(1, params.count(), CV_8U);
//    node.classDistributions = cv::Scalar(0);
//    for (int c=0; c<params.count(); ++c)
//    while (!params.isEmpty())
//        node.classDistributions.at<uchar>(0, params[c].toInt());
//    return node;
//}

//void MyDecisionForestCV::populateForest(FeatureVec featVec, Label l)
//{
//    for (int idxTree=0; idxTree < this->forest.count(); ++idxTree)
//    {
//        addSampleToTree(featVec, l, idxTree);
//    }
//}

//ClassCounts MyDecisionForestCV::testForestCC(FeatureVec featVec)
//{
////    qDebug(QString("There are %1 trees.").arg(QString::number(this->forest.count())).toAscii().constData());
//    ClassCounts cc = testSampleAtTree(featVec, 0);
//    for (int idxTree=1; idxTree<this->forest.count(); ++idxTree)
//    {
//        ClassCounts ccCurr = testSampleAtTree(featVec, idxTree);
//        if (ccCurr.cols > cc.cols)
//        {

//            cc.resize(ccCurr.size());
//        }
//        if (cc.cols > ccCurr.cols)
//        {
//            ccCurr.resize(cc.size());
//        }
//        cc= cc+ccCurr;
////        for (Label l=0; l<cc.count(); ++l)
////            cc[l]+=ccCurr[l];
//    }

//    return cc;
//}

//Label MyDecisionForestCV::testForest(FeatureVec featVec)
//{
////    qDebug(QString("There are %1 trees.").arg(QString::number(this->forest.count())).toAscii().constData());
//    ClassCounts cc = testSampleAtTree(featVec, 0);
//    for (int idxTree=1; idxTree<this->forest.count(); ++idxTree)
//    {
//        ClassCounts ccCurr = testSampleAtTree(featVec, idxTree);
//        while (ccCurr.count()>cc.count())
//            cc << 0;
//        while (cc.count()>ccCurr.count())
//            ccCurr << 0;
//        for (Label l=0; l<cc.count(); ++l)
//            cc[l]+=ccCurr[l];
//    }

//    int bestCount=0;
//    Label bestClass=0;
//    for (Label l=0; l<cc.count(); ++l)
//    {
//        if (cc[l]>bestCount)
//        {
//            bestCount = cc[l];
//            bestClass = l;
//        }
//    }

//    return bestClass;
//}

//void MyDecisionForestCV::addSampleToTree(FeatureVec featVec, Label l, int idxTree, int idxNode)
//{
//    if (this->forest[idxTree].isEmpty())
//    {
//        qDebug("What the fuck man ?");
//        return;
//    }
//    if (idxNode > this->forest[idxTree].count())
//    {
//        idxNode = qFloor(double(idxNode)/2);
//        while (this->forest[idxTree][idxNode-1].classDistributions.count() <= l)
//            this->forest[idxTree][idxNode-1].classDistributions << 0;
//        this->forest[idxTree][idxNode-1].classDistributions[l]++;
//        return;
//    }

//    if (this->forest[idxTree][idxNode-1].F1==-1)
//    {
//        while (this->forest[idxTree][idxNode-1].classDistributions.count() <= l)
//            this->forest[idxTree][idxNode-1].classDistributions << 0;
//        this->forest[idxTree][idxNode-1].classDistributions[l]++;
//        return;
//    }

//    Feature F1 = featVec[this->forest[idxTree][idxNode-1].F1];
//    Feature F2 = featVec[this->forest[idxTree][idxNode-1].F2];
//    Feature feat = F1-F2;

//    bool isRight = feat<this->forest[idxTree][idxNode-1].th;
//    idxNode=idxNode*2;
//    if (isRight)
//        idxNode++;

//    this->addSampleToTree(featVec, l, idxTree, idxNode);
//    return;
//}

//ClassCounts MyDecisionForestCV::testSampleAtTree(FeatureVec featVec, int idxTree, int idxNode)
//{
//    if (this->forest[idxTree].isEmpty())
//        return ClassCounts();
//    if (this->forest[idxTree].count()<= idxNode)
//    {
//        idxNode = qFloor(idxNode/2);
//        return this->forest[idxTree][idxNode-1].classDistributions;
//    }
//    if (this->forest[idxTree][idxNode-1].F1==-1)
//    {
//        return this->forest[idxTree][idxNode-1].classDistributions;
//    }
//    Feature F1 = featVec[this->forest[idxTree][idxNode-1].F1];
//    Feature F2 = featVec[this->forest[idxTree][idxNode-1].F2];
//    Feature feat = F1-F2;
//    bool isRight = feat<this->forest[idxTree][idxNode-1].th;
//    idxNode=idxNode*2;
//    if (isRight)
//        idxNode++;

//    return this->testSampleAtTree(featVec, idxTree, idxNode);
//}

