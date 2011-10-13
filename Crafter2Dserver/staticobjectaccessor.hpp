#ifndef STATICOBJECTACCESSOR_HPP
#define STATICOBJECTACCESSOR_HPP

#include "faccessor.hpp"

#include <gStaticObject>

class StaticObjectAccessor : public fAccessor<gStaticObject, gStaticObject>
{
public:
    StaticObjectAccessor();
};

#endif // STATICOBJECTACCESSOR_HPP
