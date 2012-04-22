#include "nearbyobjects.hpp"

Message::Screen::NearbyObjects::NearbyObjects(): Screen(NearbyObjects::s_id)
{}


Message::Message* Message::Screen::NearbyObjects::extract(QDataStream& in)
{
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

void Message::Screen::NearbyObjects::setBuildings(const type_list& lst)
{
    m_objects = lst;
}

void Message::Screen::NearbyObjects::setObjects(const type_list& lst)
{
    m_buildings = lst;
}

void Message::Screen::NearbyObjects::setStaticObjects(const type_list& lst)
{
    m_staticObjects = lst;
}

namespace {

const bool registered = Message::Message::type_factory::instance().registerClasse(Message::Screen::NearbyObjects::s_id, &Message::Screen::NearbyObjects::extract);

}
