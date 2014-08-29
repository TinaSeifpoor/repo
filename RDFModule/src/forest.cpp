#include "forest.h"
#include "node.h"
#include <QtConcurrentRun>
#include <QList>
#include <QStringList>
#include <QRegExp>
#include <QFile>
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
    Forest* f = new Forest;
    f->d = new ForestPrivate;
    f->d->pro = properties;
//    QList<QFuture<Node*> > futureNodes;
//    for (int i=0; i<(int)properties.nTrees; ++i) {
//        QFuture<Node*> futureNode = QtConcurrent::run(nodeTrainer, source,features,properties);
//        futureNodes << futureNode;
//    }

//    foreach (QFuture<Node*> futureNode, futureNodes) {
//        futureNode.waitForFinished();
//        f->d->forest << futureNode.result();
//    }
    for (int i = 0; i<(int)properties.nTrees;++i)
        f->d->forest << nodeTrainer(source, features, properties);
    return f;
}

QString Forest::text() const
{
    QStringList treeTexts;
    for (int i=0; i<d->forest.count(); ++i)
        treeTexts<<treeText.arg(i).arg(d->forest.at(i)->text());


    return forestText.arg(d->pro.baggingFactorFeatures).arg(d->pro.baggingFactorSamples).arg(d->pro.nTrees).arg(d->pro.treeProperties.baggingFactorFeatures).arg(d->pro.treeProperties.baggingFactorSamples).arg(d->pro.treeProperties.maxDepth).arg(treeTexts.join("\r\n\t"));
}

bool Forest::writeForest(QString path) const
{
    QFile file(path);
    if (file.open(QFile::WriteOnly)) {
        if (file.write(text().toLatin1())) {
            file.close();
            return true;
        }
    }
    return false;
}

Forest *Forest::fromText(QString text)
{

    text.remove("\r\n");
    text.remove("\t");

    Forest* f = new Forest;
    f->d = new ForestPrivate;

    f->d->pro.setAll(text);

    QString beginText = TreeText;
    beginText.prepend("<");
    QString endText = TreeText;
    endText.append(">");
    endText.prepend("</");


//    int nTrees = text.count(beginText);

    int previousBeginInd = -1;
    int previousEndInd = -1;
    while (true) {
        int beginInd = text.indexOf(beginText, previousBeginInd+1);
        int endInd = text.indexOf(endText, previousEndInd+1);
        if (beginInd!=-1 && endInd!=-1)
            f->d->forest << Node::treeFromText(text.mid(beginInd+beginText.length(), endInd-beginInd-beginText.length()), f->d->pro.treeProperties);
        else
            break;
        previousBeginInd = beginInd;
        previousEndInd = endInd;
    }

    return f;
}

Forest *Forest::readForest(QString path)
{
    QFile file(path);
    file.open(QFile::ReadOnly);
    Forest* f = Forest::fromText(file.readAll());
    file.close();
    return f;
}

TestResult Forest::test(const Source *source, const Features* features)
{
    TestResult result;
    for (int i=0; i<d->forest.count(); ++i) {
        Node* node = d->forest.at(i);
        result.setTreeIndex(i);
        node->testSource(source, features, &result);
    }
    return result;
}

Forest::~Forest()
{
    delete d;
}

Forest::Forest()
{
}
