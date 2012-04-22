#include "ctree.hpp"

cTree::cTree(): cStaticObject(0)
{
    //TODO yup
}

cTree::cTree(const gTree *tree): cStaticObject(tree->id()), gTree(tree->id())
{}
