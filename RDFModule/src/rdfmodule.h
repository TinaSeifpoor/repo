#ifndef RDFMODULE_H
#define RDFMODULE_H

#include <QObject>
#include "rdfmodule_global.h"
#include "source.h"
#include "common.h"
#include "decisiontreetrainer.h"

class RDFMODULESHARED_EXPORT RDFModule: public QObject
{
    Q_OBJECT
public:
    RDFModule();
    void train(Source* sourceHandle, ForestProperties propertiesHandle);
signals:
    void trainComplete(QVector<QVector<Node> >);
private:
    Source* sourceHandle;
    ForestProperties* propertiesHandle;
    QVector<QVector<Node> > forest;
    QVector<DecisionTreeTrainer*> trainers;
private slots:
    void on_treeTrainComplete(QVector<Node> tree);
};

#endif // RDFMODULE_H
