#ifndef SOBJECT_HPP
#define SOBJECT_HPP

#include "dataaccessor.hpp"
#include "sworldelement.hpp"

#include <gObject>

class sObject : public gObject, public sWorldElement
{
public:
    virtual ~sObject();

    virtual void save();

    static sObject* load(quint64 id) throw(DataAccessor::Exception);

protected:
    sObject(quint64 id);
};

#endif // SOBJECT_HPP
