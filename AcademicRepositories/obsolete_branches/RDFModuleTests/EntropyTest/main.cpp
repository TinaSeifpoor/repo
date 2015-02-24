#include <QCoreApplication>
#include "../../RDFModule/src/node.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Node node;
#ifdef random
    unsigned int maxClassCount = 10000;
    qsrand(300);
    for (int i=0; i<10; ++i) {
        unsigned int classCount = qrand()%maxClassCount;
#endif
        std::vector<unsigned int> sampleHistogram;
        unsigned int nSamples=0;
        QString classDescription("(");
#ifndef random
        sampleHistogram.push_back(10);
        sampleHistogram.push_back(15);
        unsigned int classCount = sampleHistogram.size();
#endif
        for (unsigned int j=0; j<classCount; ++j) {
#ifdef random
            sampleHistogram.push_back(qrand());
#endif
            nSamples+=sampleHistogram.at(j);
            classDescription.append(QString::number(sampleHistogram.at(j)));
            classDescription.append(",");
        }
        classDescription.chop(1);
        classDescription.append(")");
//        qDebug(classDescription.toLatin1());
        qDebug("Entropy: %f",node.entropy(sampleHistogram,nSamples));
#ifdef random
    }
#endif
    return 0;
}
