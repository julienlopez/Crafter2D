#include "getnearbyobjects.hpp"

Message::Screen::GetNearbyObjects::GetNearbyObjects(const Position& position, double distance): Screen(GetNearbyObjects::s_id)
{
    m_position = position;
    m_distance = distance;
}

Position Message::Screen::GetNearbyObjects::position() const
{
    return m_position;
}

double Message::Screen::GetNearbyObjects::distance() const
{
    return m_distance;
}

Message::Message *Message::Screen::GetNearbyObjects::extract(QDataStream& in)
{
    Position position;
    double distance;
    in >> position;
    in >> distance;
    return new GetNearbyObjects(position, distance);
}

QDataStream& Message::Screen::GetNearbyObjects::serialize(QDataStream& out) const
{
    out << m_id;
    out << m_position;
    out << m_distance;
    return out;
}

namespace {

const bool registered = Message::Message::type_factory::instance().registerClasse(Message::Screen::GetNearbyObjects::s_id, &Message::Screen::GetNearbyObjects::extract);

}
