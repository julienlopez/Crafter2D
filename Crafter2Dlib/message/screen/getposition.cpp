#include "getposition.hpp"

Message::Screen::GetPosition::GetPosition(): Screen(GetPosition::s_id)
{}

Message::Screen::GetPosition* Message::Screen::GetPosition::extract(QDataStream& in, quint64 id)
{
    Q_ASSERT(id == GetPosition::s_id);
    return new GetPosition;
}

QDataStream& Message::Screen::GetPosition::serialize(QDataStream& out) const
{
    out << m_id;
    return out;
}
