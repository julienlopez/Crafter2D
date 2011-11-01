#ifndef SOBJECT_HPP
#define SOBJECT_HPP

#include "dataaccessor.hpp"
#include "sworldelement.hpp"

#include <gObject>

class sObject : public gObject, public sWorldElement
{
public:
    sObject(quint64 id) throw(DataAccessor::Exception);
    virtual ~sObject();

    virtual void save();
};

#endif // SOBJECT_HPP
