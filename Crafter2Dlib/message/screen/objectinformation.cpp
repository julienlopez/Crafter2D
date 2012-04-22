#include "objectinformation.hpp"

#include <WorldElement>

Message::Screen::ObjectInformation::ObjectInformation(WorldElement* element) :
    Screen(ObjectInformation::s_id), m_element(element)
{}

WorldElement* Message::Screen::ObjectInformation::element()
{
    return m_element;
}

Message::Message* Message::Screen::ObjectInformation::extract(QDataStream& in)
{
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

namespace {

const bool registered = Message::Message::type_factory::instance().registerClasse(Message::Screen::ObjectInformation::s_id, &Message::Screen::ObjectInformation::extract);

}
