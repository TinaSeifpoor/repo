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
    void train(const Source *samples, const Features *features, const TreeProperties properties, Source *samplesTrue, Source *samplesFalse);
};

#endif // NODE_H
