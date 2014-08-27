#include <QCoreApplication>
#include <ctime>
#include <QDir>
#include "initializer.h"
#include "forest.h"
#include "featurestest.h"
#include <QFile>
#include <QDateTime>
Q_DECLARE_METATYPE(QFileInfo);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    srand(QDateTime::currentMSecsSinceEpoch());


    Initializer init;
    Source* s = init.getSource();

    FeaturesTest f;


    TreeProperties treePro;
    treePro.baggingFactorFeatures = 1;
    treePro.baggingFactorSamples = 1;
    treePro.maxDepth = 4;


    ForestProperties forestPro;
    forestPro.baggingFactorFeatures = 1;
    forestPro.baggingFactorSamples = 1;
    forestPro.nTrees = 1;
    forestPro.treeProperties = treePro;
    qDebug("training forest...");
    Forest* forest = Forest::train(s, &f, forestPro);
    qDebug("forest trained");
    QFile file("d:/forest.xml");
    file.open(QFile::WriteOnly);
    QString forestText = forest->text();
    file.write(forestText.toLatin1());
    file.close();
    qDebug("file written");
    delete forest;

    Forest* forest2 = Forest::fromText(forestText);

    return 0;
}
