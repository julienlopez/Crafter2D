#include "getnearbyobjects.hpp"

Message::Screen::GetNearbyObjects::GetNearbyObjects(const Position& position): Screen(GetNearbyObjects::s_id)
{
}

Position Message::Screen::GetNearbyObjects::position() const
{
    return m_position;
}

Message::Message *Message::Screen::GetNearbyObjects::extract(QDataStream& in)
{
    Position position;
    in >> position;
    return new GetNearbyObjects(position);
}

QDataStream& Message::Screen::GetNearbyObjects::serialize(QDataStream& out) const
{
    out << m_id;
    return out;
}

namespace {

const bool registered = Message::Message::type_factory::instance().registerClasse(Message::Screen::GetNearbyObjects::s_id, &Message::Screen::GetNearbyObjects::extract);

}
