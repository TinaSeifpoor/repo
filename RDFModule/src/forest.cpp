#include "forest.h"
#include "foresttrainer.h"
#include "node.h"
#include <QtConcurrentRun>
#include <QList>
#include "source.h"
#include "features.h"
#include <QStringList>

const QString forestText("<Forest>\r\n\t%1\r\n</Forest>");
const QString treeText("<Tree %1>\r\n\t\t%2\r\n\t</Tree>");

extern Node* nodeTrainer(const Source *source, const Features *features, const ForestProperties properties){
    return Node::train(source->baggedSamples(properties.baggingFactorSamples),
                       features->baggedFeatures(properties.baggingFactorFeatures),
                       properties.treeProperties);
}
struct ForestPrivate {
    QList<Node*> forest;
};

Forest* Forest::train(const Source *source, const Features *features, const ForestProperties properties)
{
    Forest* f = new Forest;
    f->d = new ForestPrivate;
    QList<QFuture<Node*> > futureNodes;
    for (int i=0; i<properties.nTrees; ++i) {
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

    return forestText.arg(treeTexts.join("\r\n\t"));
}

Forest::Forest()
{
}
