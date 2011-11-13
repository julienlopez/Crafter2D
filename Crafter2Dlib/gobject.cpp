#include "gobject.hpp"

gObject::gObject(quint64 id): WorldElement(id)
{
}

void gObject::serialize(QDataStream& out) const
{
    out << s_code << id();
}

gObject* gObject::extract(QDataStream& in)
{
    quint64 id;
    in >> id;
    return new gObject(id);
}
