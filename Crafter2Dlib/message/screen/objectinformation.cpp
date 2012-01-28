#include "objectinformation.hpp"

#include <WorldElement>

Message::Screen::ObjectInformation::ObjectInformation(WorldElement* element) :
    Screen(ObjectInformation::s_id), m_element(element)
{}

WorldElement* Message::Screen::ObjectInformation::element()
{
    return m_element;
}

Message::Screen::ObjectInformation::ObjectInformation* Message::Screen::ObjectInformation::extract(QDataStream& in, quint64 id)
{
    Q_ASSERT(id == ObjectInformation::s_id);
    ObjectInformation* res = new ObjectInformation;
    res->m_element = WorldElement::extract(in);
    Q_ASSERT(res->m_element);
    return res;
}

QDataStream& Message::Screen::ObjectInformation::serialize(QDataStream& out) const
{
    out << id();
    m_element->serialize(out);
    return out;
}
