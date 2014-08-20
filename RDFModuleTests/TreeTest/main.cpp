#include <QCoreApplication>
#include <ctime>
#include <QDir>
#include "featurestest.h"
#include "node.h"
#include "common.h"
#include "vectorindexsorter.h"
#include "initializer.h"
Q_DECLARE_METATYPE(QFileInfo);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    srand(time(0));


    Initializer init;
    Source s = init.getSource();

    FeaturesTest f;

    TreeProperties pro;
    pro.baggingFactorFeatures = 1;
    pro.baggingFactorSamples = 1;
    pro.maxDepth = 3;
    Node* n0 = Node::train(&s,&f,pro);
    Node* n1 = Node::trainLeft(n0);
    Node* n2 = Node::trainRight(n0);
//    Source sourceTrue, sourceFalse;
//    n.train(&s,&f,pro,&sourceTrue, &sourceFalse);
    return 0;
}
