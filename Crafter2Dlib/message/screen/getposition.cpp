#include "getposition.hpp"

#include <cassert>

Message::Screen::GetPosition::GetPosition(): Screen(GetPosition::s_id)
{}

Message::Screen::GetPosition* Message::Screen::GetPosition::extract(QDataStream& in, quint64 id)
{
    assert(id == GetPosition::s_id);
    return new GetPosition;
}

QDataStream& Message::Screen::GetPosition::serialize(QDataStream& out) const
{
    out << m_id;
    return out;
}
