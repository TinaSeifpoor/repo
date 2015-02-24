#include <QCoreApplication>
#include <ctime>
#include <QDir>
#include "sourcetest.h"
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
    pro.criteria = GiniImpurity;
    pro.maxDepth = 3;
    Node n;
    Source* sourceTrue=0, *sourceFalse=0;
    n.train(&s,&f,pro,sourceTrue, sourceFalse);
    return 0;
}
