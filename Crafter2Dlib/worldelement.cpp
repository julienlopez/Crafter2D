#include "worldelement.hpp"
#include "gplayer.hpp"
#include "gbuilding.hpp"
#include "gobject.hpp"
#include "gstaticobject.hpp"

WorldElement::WorldElement(quint64 id, const Position& position): m_id(id), m_position(position)
{}

quint64 WorldElement::id() const
{
    return m_id;
}

Position WorldElement::position() const
{
    return m_position;
}

void WorldElement::setPosition(const Position& p)
{
    m_position = p;
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

    Position pos;
    in >> id;
    in >> pos;
    return new WorldElement(id, pos);
}
