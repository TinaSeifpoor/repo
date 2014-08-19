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
    //
    static Node* train(const Source *source, const Features *features, const TreeProperties properties);

    static Node* trainLeft(Node* parent);
    static Node* trainRight(Node* parent);

    const Features* features() const;
    TreeProperties treeProperties() const;
    const Source* leftSamples() const;
    const Source* rightSamples() const;
    double splitValue() const;
    unsigned int featureIdx() const;

private:
    Node(const Source *source, const Features *features, TreeProperties properties, Source* left, Source* right, double splitValue, unsigned int featureIdx);
    NodePrivate* d;
};

#endif // NODE_H
