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
