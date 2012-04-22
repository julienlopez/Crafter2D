#ifndef STREE_HPP
#define STREE_HPP

#include "sstaticobject.hpp"

#include <gTree>

class sTree : virtual gStaticObject, public gTree, public sStaticObject
{
public:
    sTree(quint64 id);

    virtual bool setData(QString data);
};

#endif // STREE_HPP
