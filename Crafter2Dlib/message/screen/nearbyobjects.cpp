#include "nearbyobjects.hpp"

Message::Screen::NearbyObjects::NearbyObjects(): Screen(NearbyObjects::s_id)
{}


Message::Screen::NearbyObjects::NearbyObjects* Message::Screen::NearbyObjects::extract(QDataStream& in, quint64 id)
{
    Q_ASSERT(id == NearbyObjects::s_id);
    NearbyObjects* res = new NearbyObjects;
    in >> res->m_buildings;
    in >> res->m_objects;
    in >> res->m_staticObjects;
    return res;
}

QDataStream& Message::Screen::NearbyObjects::serialize(QDataStream& out) const
{
    out << s_id;
    out << m_buildings;
    out << m_objects;
    out << m_staticObjects;
    return out;
}

Message::Screen::NearbyObjects::type_list Message::Screen::NearbyObjects::objects() const
{
    return m_objects;
}

Message::Screen::NearbyObjects::type_list Message::Screen::NearbyObjects::buildings() const
{
    return m_buildings;
}

Message::Screen::NearbyObjects::type_list Message::Screen::NearbyObjects::staticObjects() const
{
    return m_staticObjects;
}