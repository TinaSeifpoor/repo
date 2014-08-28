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
    static Node* train(const Source *source, const Features *features, const TreeProperties properties, int linearIdx=0);
    QString text() const;
    static Node* treeFromText(QString text, TreeProperties pro);
    static Node* nodeFromText(QString text, TreeProperties pro);

    ~Node();
private:
    Node(const int linearIdx, const Source *source, const Features *features, TreeProperties properties, Source* left, Source* right, double splitValue, int featureIdx, double parentEntropy, double leftEntropy, double rightEntropy, double informationGain);
    Node(const int linearIdx, TreeProperties properties, double splitValue, int featureIdx, double parentEntropy, QList<ClassID> uniqueClasses, QList<ClassID> classes);
    NodePrivate* d;
};

#endif // NODE_H
