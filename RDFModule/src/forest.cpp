#include "forest.h"
#include "node.h"
#include <QtConcurrentRun>
#include <QList>
#include <QStringList>
#include <QRegExp>
#include "source.h"
#include "features.h"
#include "common.h"


const QString forestText("<Forest><BaggingFactorFeaturesTree>%1</BaggingFactorFeaturesTree><BaggingFactorSamplesTree>%2</BaggingFactorSamplesTree><ForestSize>%3</ForestSize><BaggingFactorFeaturesNode>%4</BaggingFactorFeaturesNode><BaggingFactorSamplesNode>%5</BaggingFactorSamplesNode><MaxDepth>%6</MaxDepth>\r\n\t%7\r\n</Forest>");
const QString treeText("<Tree %1>\r\n\t\t%2\r\n\t</Tree>");

extern Node* nodeTrainer(const Source *source, const Features *features, const ForestProperties properties){
    qDebug("training tree...");
    return Node::train(source->baggedSamples(properties.baggingFactorSamples),
                       features->baggedFeatures(properties.baggingFactorFeatures),
                       properties.treeProperties);
}
struct ForestPrivate {
    QList<Node*> forest;
    ForestProperties pro;
    ~ForestPrivate() {
        foreach (Node* node, forest) {
            delete node;
        }
    }
};

Forest* Forest::train(const Source *source, const Features *features, const ForestProperties properties)
{
    qDebug("training tree...");
    Forest* f = new Forest;
    f->d = new ForestPrivate;
    f->d->pro = properties;
    QList<QFuture<Node*> > futureNodes;
    for (int i=0; i<(int)properties.nTrees; ++i) {
        QFuture<Node*> futureNode = QtConcurrent::run(nodeTrainer, source,features,properties);
        futureNodes << futureNode;
    }

    foreach (QFuture<Node*> futureNode, futureNodes) {
        futureNode.waitForFinished();
        f->d->forest << futureNode.result();
    }
    return f;
}

QString Forest::text() const
{
    QStringList treeTexts;
    for (int i=0; i<d->forest.count(); ++i)
        treeTexts<<treeText.arg(i).arg(d->forest.at(i)->text());

    return forestText.arg(d->pro.baggingFactorFeatures).arg(d->pro.baggingFactorSamples).arg(d->pro.nTrees).arg(d->pro.treeProperties.baggingFactorFeatures).arg(d->pro.treeProperties.baggingFactorSamples).arg(d->pro.treeProperties.maxDepth).arg(treeTexts.join("\r\n\t"));
}

Forest *Forest::fromText(QString text)
{
    QStringList lines = text.split("\r\n", QString::SkipEmptyParts);
    QString forestDescription = lines.takeFirst();

    QStringList forestPropertiesKeywords = QStringList()    << BaggingFactorFeaturesTree
                                                            << BaggingFactorFeaturesTree
                                                            << BaggingFactorSamplesTree
                                                            << ForestSize
                                                            << BaggingFactorFeaturesNode
                                                            << BaggingFactorSamplesNode
                                                            << MaxDepth;

    ForestProperties pro;
    foreach (QString forestPropertiesKeyword, forestPropertiesKeywords) {
        QString beginText = forestPropertiesKeyword;
        beginText.prepend("<");
        beginText.append(">");
        QString endText = forestPropertiesKeyword;
        endText.append(">");
        endText.prepend("</");
        int beginInd = forestDescription.indexOf(beginText);
        int endInd = forestDescription.indexOf(endText);
        QString text = forestDescription.mid(beginInd+beginText.length(), endInd-beginInd-beginText.length());
        pro.set(forestPropertiesKeyword,text);
    }
    return 0;
}

Forest::~Forest()
{
    delete d;
}

Forest::Forest()
{
}
