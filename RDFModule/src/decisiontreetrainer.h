#ifndef DECISIONTREETRAINER_H
#define DECISIONTREETRAINER_H

#include "tree.h"
#include "common.h"
#include "node.h"
#include "source.h"
#include "qmath.h"
#include <QVector>
#include <QThread>
class DecisionTreeTrainer : public QThread
{
    Q_OBJECT
public:
    DecisionTreeTrainer();
    void train(Source* samples, TreeProperties properties);

signals:
    void treeTrainComplete(QVector<Node>);
private:
    void trainRecursiveNode(Source* samples, TreeProperties properties, unsigned int currentIdx);
    QVector<Node> nodes;
};

#endif // DECISIONTREETRAINER_H
