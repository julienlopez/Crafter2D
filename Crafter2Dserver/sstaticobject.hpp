#ifndef SSTATICOBJECT_HPP
#define SSTATICOBJECT_HPP

#include "dataaccessor.hpp"
#include "sworldelement.hpp"

#include <gStaticObject>

class sStaticObject : public gStaticObject, public sWorldElement
{
public:
    sStaticObject(quint64 id) throw(DataAccessor::Exception);
    virtual ~sStaticObject();

    virtual void save();
};

#endif // SSTATICOBJECT_HPP
