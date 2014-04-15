#ifndef NODE_H
#define NODE_H

#include "common.h"
#include "source.h"
#include <QVector>
class Node
{
public:
    Node();
    void train(Source* samples, TreeProperties properties, Source* samplesTrue, Source* samplesFalse);

private:
    bool splitFunction();
};

#endif // NODE_H
