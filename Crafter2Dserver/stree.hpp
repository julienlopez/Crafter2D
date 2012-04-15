#ifndef STREE_HPP
#define STREE_HPP

#include "sstaticobject.hpp"

#include <gTree>

class sTree : virtual gStaticObject, public gTree, public sStaticObject
{
public:
    sTree(quint64 id);

    static const Type s_type = 0;

    virtual bool setData(QString data);
};

#endif // STREE_HPP
