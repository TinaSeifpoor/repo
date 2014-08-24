#include "tree.h"
#include "node.h"
Tree *Tree::trainTree(const Source *source, const Features *features, const TreeProperties properties)
{
    Node* a = Node::train(source, features, properties, 0);
return 0;
}

Tree::Tree()
{
}
