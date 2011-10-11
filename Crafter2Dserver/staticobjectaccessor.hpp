#ifndef STATICOBJECTACCESSOR_HPP
#define STATICOBJECTACCESSOR_HPP

#include "faccessor.hpp"

#include <StaticObject>

class StaticObjectAccessor : public fAccessor<StaticObject>
{
public:
    StaticObjectAccessor();
};

#endif // STATICOBJECTACCESSOR_HPP
