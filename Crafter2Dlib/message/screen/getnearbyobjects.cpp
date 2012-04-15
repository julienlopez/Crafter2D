#include "getnearbyobjects.hpp"

Message::Screen::GetNearbyObjects::GetNearbyObjects(const Position& position): Screen(GetNearbyObjects::s_id)
{
}

Position Message::Screen::GetNearbyObjects::position() const
{
    return m_position;
}

Message::Screen::GetNearbyObjects* Message::Screen::GetNearbyObjects::extract(QDataStream& in, quint64 id)
{
    Q_ASSERT(id == GetNearbyObjects::s_id);
    Position position;
    in >> position;
    return new GetNearbyObjects(position);
}

QDataStream& Message::Screen::GetNearbyObjects::serialize(QDataStream& out) const
{
    out << m_id;
    return out;
}
