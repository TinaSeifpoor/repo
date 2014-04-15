#include "rdfmodule.h"


RDFModule::RDFModule()
{
}

void RDFModule::train(Source* sourceHandle, ForestProperties propertiesHandle)
{
//    unsigned int nSamples = sourceHandle->countSamples();
//    unsigned int nFeatures = sourceHandle->countFeatures();
    unsigned int nTree = propertiesHandle.nTrees;
    for (unsigned int i=0; i<nTree; ++i)
    {
        Source* treeSource = sourceHandle->baggedSamples(propertiesHandle.baggingFactorSamples, propertiesHandle.baggingFactorSamples);
        DecisionTreeTrainer* tree = new DecisionTreeTrainer;
        connect (tree, SIGNAL(treeTrainComplete(QVector<Node>)), this, SLOT(on_treeTrainComplete(QVector<Node>)));
        tree->train(treeSource, propertiesHandle.treeProperties);
    }
}


void RDFModule::on_treeTrainComplete(QVector<Node> tree)
{
    forest << tree;
}
