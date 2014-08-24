#include <QCoreApplication>
#include <ctime>
#include <QDir>
#include "initializer.h"
#include "forest.h"
#include "featurestest.h"
#include <QFile>
Q_DECLARE_METATYPE(QFileInfo);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    srand(time(0));


    Initializer init;
    Source s = init.getSource();

    FeaturesTest f;


    TreeProperties treePro;
    treePro.baggingFactorFeatures = 1;
    treePro.baggingFactorSamples = 1;
    treePro.maxDepth = 3;


    ForestProperties forestPro;
    forestPro.baggingFactorFeatures = 1;
    forestPro.baggingFactorSamples = 1;
    forestPro.nTrees = 500;
    forestPro.treeProperties = treePro;
    Forest* forest = Forest::train(&s, &f, forestPro);
    QFile file("d:/forest.xml");
    file.open(QFile::WriteOnly);
    file.write(forest->text().toLatin1());
    file.close();
//    Source sourceTrue, sourceFalse;
//    n.train(&s,&f,pro,&sourceTrue, &sourceFalse);
    return 0;
}
