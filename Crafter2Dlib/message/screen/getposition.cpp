#include "getposition.hpp"

#include <cassert>

Message::Screen::GetPosition::GetPosition(): Screen(5001)
{}

Message::Screen::GetPosition* Message::Screen::GetPosition::extract(QDataStream& in, quint64 id)
{
    assert(id == 5001);
    return new GetPosition;
}

QDataStream& Message::Screen::GetPosition::serialize(QDataStream& out) const
{
    out << m_id;
    return out;
}
