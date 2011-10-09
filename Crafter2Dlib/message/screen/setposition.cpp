#include "setposition.hpp"

#include <cassert>

Message::Screen::SetPosition::SetPosition(const Position& position): Screen(5002), m_position(position)
{}

Position Message::Screen::SetPosition::position() const
{
    return m_position;
}

Message::Screen::SetPosition* Message::Screen::SetPosition::extract(QDataStream& in, quint64 id)
{
    assert(id == 5002);
    Position p;
    in >> p;
    return new SetPosition(p);
}

QDataStream& Message::Screen::SetPosition::serialize(QDataStream& out) const
{
    out << m_id;
    out << m_position;
    return out;
}
