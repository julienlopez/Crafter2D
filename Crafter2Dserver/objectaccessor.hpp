#ifndef OBJECTACCESSOR_HPP
#define OBJECTACCESSOR_HPP

#include "faccessor.hpp"
#include "sobject.hpp"

class ObjectAccessor : public fAccessor<gObject, sObject>
{
public:
    ObjectAccessor();
};

#endif // OBJECTACCESSOR_HPP
