#include "gstaticobject.hpp"

gStaticObject::gStaticObject(quint64 id): WorldElement(id)
{
}

void gStaticObject::serialize(QDataStream& out) const
{
    out << s_code << id();
}

gStaticObject* gStaticObject::extract(QDataStream& in)
{
    quint64 id;
    in >> id;
    return new gStaticObject(id);
}

quint64 gStaticObject::code() const
{
    return s_code;
}

gStaticObject::Type gStaticObject::type() const
{
    return 0;
}
