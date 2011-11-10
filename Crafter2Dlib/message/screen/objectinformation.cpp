#include "objectinformation.hpp"

//#include <

#include <cassert>

Message::Screen::ObjectInformation::ObjectInformation() :
    Screen(5004)
{
}

Message::Screen::ObjectInformation::ObjectInformation* Message::Screen::ObjectInformation::extract(QDataStream& in, quint64 id)
{
    assert(id == 5004);
    if(m_element != 0) delete m_element;
    m_element = WorldElement::extract(in);

    return new ObjectInformation;
}

QDataStream& Message::Screen::ObjectInformation::serialize(QDataStream& out) const
{
    out << id();
    m_element->serialize(out);
    return out;
}
