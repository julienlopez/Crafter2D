#include "sstaticobject.hpp"

sStaticObject::sStaticObject(quint64 id) throw(DataAccessor::Exception): gStaticObject(id)
{
}

sStaticObject::~sStaticObject()
{
}

void sStaticObject::save()
{
}
