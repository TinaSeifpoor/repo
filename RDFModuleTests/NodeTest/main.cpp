#include <QCoreApplication>
#include <ctime>
#include <QDir>
#include "sourcetest.h"
#include "featurestest.h"
#include "../../RDFModule/src/node.h"
#include "../../RDFModule/src/common.h"
#include "../../RDFModule/src/vectorindexsorter.h"

int main(int argc, char *argv[])
{
//    QCoreApplication a(argc, argv);
    srand(time(0));

    std::vector<int> a;
    a.push_back(10);
    a.push_back(3);
    a.push_back(25);
    a.push_back(25);
    a.push_back(25);
    a.push_back(25);
    a.push_back(25);
    std::vector<unsigned int> i = sort_indexes(a);










    FeaturesTest f;
    QDir dir1("D:/classes/1");
    QDir dir2("D:/classes/2");
    QFileInfoList samples1= dir1.entryInfoList(QDir::Dirs|QDir::NoDotAndDotDot, QDir::Unsorted);
    QFileInfoList samples2= dir2.entryInfoList(QDir::Dirs|QDir::NoDotAndDotDot, QDir::Unsorted);

    QList<Sample> samples;
    for (int i=0;i<samples1.count();++i) {
        Sample s;
        s.sampleClass = 0;
        s.sampleSource = QVariant::fromValue<QFileInfo>(samples1.at(i));
        samples << s;
    }
    for (int i=0;i<samples2.count();++i) {
        Sample s;
        s.sampleClass = 1;
        s.sampleSource = QVariant::fromValue<QFileInfo>(samples2.at(i));
        samples << s;
    }
    Source s(samples);
    Source* baggedSamples = s.baggedSamples(0.1);
    Features* baggedFeatures = f.randomlySortedList(0.1);
    TreeProperties pro;
    pro.baggingFactorFeatures = 0.1;
    pro.baggingFactorSamples = 0.6;
    pro.criteria = GiniImpurity;
    pro.maxDepth = 3;
    Node n;
    Source* samplesTrue, *samplesFalse;
    n.train(baggedSamples,baggedFeatures,pro,samplesTrue, samplesFalse);
    return 0;
}
