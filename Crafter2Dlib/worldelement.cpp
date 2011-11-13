#include "worldelement.hpp"
#include "gplayer.hpp"
#include "gbuilding.hpp"
#include "gobject.hpp"
#include "gstaticobject.hpp"

WorldElement::WorldElement(quint64 id): m_id(id)
{}

quint64 WorldElement::id() const
{
    return m_id;
}

void WorldElement::serialize(QDataStream& out) const
{
    out << 0 << m_id;
}

WorldElement* WorldElement::extract(QDataStream& in)
{
    quint64 c, id;
    in >> c;
    if(c == gPlayer::s_code) return gPlayer::extract(in);
    if(c == gBuilding::s_code) return gBuilding::extract(in);
    if(c == gObject::s_code) return gObject::extract(in);
    if(c == gStaticObject::s_code) return gStaticObject::extract(in);

    in >> id;
    return new WorldElement(id);
}
