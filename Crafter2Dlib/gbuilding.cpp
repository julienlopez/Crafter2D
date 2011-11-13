#include "gbuilding.hpp"

gBuilding::gBuilding(quint64 id): WorldElement(id)
{
}

void gBuilding::serialize(QDataStream& out) const
{
    out << s_code << id();
}

gBuilding* gBuilding::extract(QDataStream& in)
{
    quint64 id;
    in >> id;
    return new gBuilding(id);
}
