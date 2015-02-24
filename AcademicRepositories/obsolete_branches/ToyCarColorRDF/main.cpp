#include "mainwindow.h"
#include <QApplication>
#include "initializer.h"
#include "imagecolorfeatures.h"
#include "forest.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Source* s = Initializer::getSource();
    ImageColorFeatures features;

    TreeProperties treePro;
    treePro.baggingFactorFeatures = 1;
    treePro.baggingFactorSamples = 1;
    treePro.maxDepth = 3;


    ForestProperties forestPro;
    forestPro.baggingFactorFeatures = 1;
    forestPro.baggingFactorSamples = 1;
    forestPro.nTrees = 50;
    forestPro.treeProperties = treePro;
    qDebug("training forest...");
    Forest* forest = Forest::train(s, &features, forestPro);
    qDebug("forest trained");
    forest->writeForest("d:/forest.xml");
    qDebug("file written");

    TestResult t = forest->test(s,&features);


    int positive=0, negative=0;
    QHash<QString, ClassID> hash = s->getSampleID();
    foreach (QString sampleName, hash.keys()) {
        ClassID testResult = t.getSampleClassMajority(sampleName);
        ClassID trainResult = hash.value(sampleName);
        if (testResult==trainResult) {
            ++positive;
        } else {
            ++negative;
        }
    }
    qDebug("Positive:");
    qDebug(QString::number(positive).toLatin1());
    qDebug("Negative:");
    qDebug(QString::number(negative).toLatin1());

    return 0;
}
