#include <QCoreApplication>
#include <ctime>
#include <QDir>
#include "initializer.h"
#include "forest.h"
#include "featurestest.h"
#include <QFile>
#include <QDateTime>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    srand(QDateTime::currentMSecsSinceEpoch());


    Initializer init;
    Source* s = init.getSource();

    FeaturesTest f;


    TreeProperties treePro;
    treePro.baggingFactorFeatures = 0.6;
    treePro.baggingFactorSamples = 0.6;
    treePro.maxDepth = 3;


    ForestProperties forestPro;
    forestPro.baggingFactorFeatures = 0.6;
    forestPro.baggingFactorSamples = 0.6;
    forestPro.nTrees = 8;
    forestPro.treeProperties = treePro;
    qDebug("training forest...");
    Forest* forest = Forest::train(s, &f, forestPro);
    qDebug("forest trained");
    forest->writeForest("d:/forest.xml");
    qDebug("file written");
//    s->writeToDisk(&f, "d:/sources.txt");
    delete forest;

    Forest* forest2 = Forest::readForest("d:/forest.xml");
    forest2->writeForest("d:/forest2.xml");

    Source* sReduced = s->baggedSamples(1);
    TestResult t = forest2->test(sReduced,&f);


    int positive=0, negative=0;
    QHash<QString, ClassID> hash = sReduced->getSampleID();
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
