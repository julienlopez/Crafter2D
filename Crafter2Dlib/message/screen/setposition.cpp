#include "setposition.hpp"

#include <cassert>

Message::Screen::SetPosition::SetPosition(const Position& position): Screen(SetPosition::s_id), m_position(position)
{}

Position Message::Screen::SetPosition::position() const
{
    return m_position;
}

Message::Screen::SetPosition* Message::Screen::SetPosition::extract(QDataStream& in, quint64 id)
{
    assert(id == SetPosition::s_id);
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
