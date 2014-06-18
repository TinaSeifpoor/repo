#ifndef NODE_H
#define NODE_H

#include "common.h"
#include "source.h"
#include <QVector>
class Node
{
public:
    Node();
    void train(const Source* samples, const TreeProperties properties, Source* samplesTrue, Source* samplesFalse);

    double entropy(std::vector<unsigned int> sampleHistogram);
};

#endif // NODE_H
