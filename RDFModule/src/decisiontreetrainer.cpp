#include "decisiontreetrainer.h"

void DecisionTreeTrainer::train(Source* samples, TreeProperties properties)
{
    this->nodes.clear();
    nodes.reserve((int)qPow(2,properties.maxDepth)-1);
    this->trainRecursiveNode(samples, properties, 0);
    emit treeTrainComplete(this->nodes);
}

void DecisionTreeTrainer::trainRecursiveNode(Source* samples, TreeProperties properties, unsigned int currentIdx)
{
    unsigned int currentDepth =  (unsigned int) floor(log((double)currentIdx)/log2);
    if (properties.maxDepth <=currentDepth)
        return;
    Source* samplesTrue, *samplesFalse;
    Node currentNode;
    currentNode.train(samples, properties, samplesTrue, samplesFalse);
    this->nodes[currentIdx] = currentNode;
    unsigned int idxTrue = 2*currentIdx+1;
    this->trainRecursiveNode(samplesTrue, properties, idxTrue);
    unsigned int idxFalse = 2*currentIdx+2;
    this->trainRecursiveNode(samplesFalse, properties, idxFalse);
}

DecisionTreeTrainer::DecisionTreeTrainer()
{
}
