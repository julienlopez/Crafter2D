#include "sendposition.hpp"

#include <cassert>

Message::Screen::SendPosition::SendPosition(const Position& position): Screen(5003), m_position(position)
{}

Position Message::Screen::SendPosition::position() const
{
    return m_position;
}

Message::Screen::SendPosition* Message::Screen::SendPosition::extract(QDataStream& in, quint64 id)
{
    assert(id == 5003);
    Position p;
    in >> p;
    return new SendPosition(p);
}

QDataStream& Message::Screen::SendPosition::serialize(QDataStream& out) const
{
    out << m_id;
    out << m_position;
    return out;
}