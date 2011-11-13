#include "objectinformation.hpp"

#include <WorldElement>

#include <cassert>

Message::Screen::ObjectInformation::ObjectInformation() :
    Screen(ObjectInformation::s_id), m_element(0)
{}

Message::Screen::ObjectInformation::ObjectInformation* Message::Screen::ObjectInformation::extract(QDataStream& in, quint64 id)
{
    assert(id == ObjectInformation::s_id);
    ObjectInformation* res = new ObjectInformation;
    res->m_element = WorldElement::extract(in);
    return res;
}

QDataStream& Message::Screen::ObjectInformation::serialize(QDataStream& out) const
{
    out << id();
    m_element->serialize(out);
    return out;
}
