#ifndef OBJECTACCESSOR_HPP
#define OBJECTACCESSOR_HPP

#include "faccessor.hpp"

#include <gObject>

class ObjectAccessor : public fAccessor<gObject, gObject>
{
public:
    ObjectAccessor();
};

#endif // OBJECTACCESSOR_HPP
