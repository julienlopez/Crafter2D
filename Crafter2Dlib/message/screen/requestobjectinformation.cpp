#include "requestobjectinformation.hpp"

#include <cassert>

Message::Screen::RequestObjectInformation::RequestObjectInformation(quint64 code, quint64 id): Screen(s_id), m_code(code), m_id(id)
{}

quint64 Message::Screen::RequestObjectInformation::code() const
{
    return m_code;
}

quint64 Message::Screen::RequestObjectInformation::id() const
{
    return m_id;
}

Message::Screen::RequestObjectInformation::RequestObjectInformation* Message::Screen::RequestObjectInformation::extract(QDataStream& in, quint64 id)
{
    assert(id == RequestObjectInformation::s_id);
    quint64 code, i;
    in >> code;
    in >> i;
    return new RequestObjectInformation(code,i);
}

QDataStream& Message::Screen::RequestObjectInformation::serialize(QDataStream& out) const
{
    out << id();
    out << m_code;
    out << m_id;
    return out;
}
