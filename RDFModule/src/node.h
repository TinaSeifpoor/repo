#ifndef NODE_H
#define NODE_H

#include "common.h"
#include <QVector>
class Source;
class Features;
class Node
{
public:
    Node();
    double entropy(std::vector<unsigned int> sampleHistogram, unsigned int nSamples);
    void train(const Source *source, const Features *features, const TreeProperties properties, Source *sourceTrue, Source *sourceFalse);
};

#endif // NODE_H
