#ifndef SSTATICOBJECT_HPP
#define SSTATICOBJECT_HPP

#include "dataaccessor.hpp"
#include "sworldelement.hpp"

#include <gStaticObject>

class sStaticObject : virtual public gStaticObject, public sWorldElement
{
public:
    typedef quint32 Type;

    virtual ~sStaticObject();

    virtual void save();

    static sStaticObject* load(quint64 id) throw(DataAccessor::Exception);

    virtual bool setData(QString data) =0;

protected:
    sStaticObject(quint64 id);

    static sStaticObject* instanciate(Type type, quint64 id);
};

#endif // SSTATICOBJECT_HPP
