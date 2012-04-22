#ifndef CTREE_HPP
#define CTREE_HPP

#include "cstaticobject.hpp"

#include <gTree>

class cTree : public cStaticObject, public gTree
{
    Q_OBJECT
public:
    cTree();
    cTree(const gTree* tree);
    
signals:
    
public slots:
    
};

#endif // CTREE_HPP
