#ifndef TREE_H
#define TREE_H
class Source;
class Features;
class Node;
struct TreeProperties;
struct TreePrivate;
class Tree
{
public:
    static Tree* trainTree(const Source *source, const Features *features, const TreeProperties properties);
protected:
    void addNode(Node*);
private:
    Tree();
    TreePrivate* d;
};

#endif // TREE_H
