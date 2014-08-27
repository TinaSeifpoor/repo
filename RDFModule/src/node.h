#ifndef NODE_H
#define NODE_H

#include "common.h"
#include <QVector>
class Source;
class Features;
struct NodePrivate;
class Node
{
public:
    static Node* train(const Source *source, const Features *features, const TreeProperties properties, unsigned int linearIdx=0);
    QString text() const;
    ~Node();
private:
    Node(const unsigned int linearIdx, const Source *source, const Features *features, TreeProperties properties, Source* left, Source* right, double splitValue, unsigned int featureIdx, double parentEntropy, double leftEntropy, double rightEntropy, double informationGain);
    NodePrivate* d;
};

#endif // NODE_H
