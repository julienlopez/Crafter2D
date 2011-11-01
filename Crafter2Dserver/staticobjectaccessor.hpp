#ifndef STATICOBJECTACCESSOR_HPP
#define STATICOBJECTACCESSOR_HPP

#include "faccessor.hpp"
#include "sstaticobject.hpp"

class StaticObjectAccessor : public fAccessor<gStaticObject, sStaticObject>
{
public:
    StaticObjectAccessor();
};

#endif // STATICOBJECTACCESSOR_HPP
