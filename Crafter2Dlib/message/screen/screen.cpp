#include "screen.hpp"
#include "getposition.hpp"
#include "setposition.hpp"
#include "sendposition.hpp"

#include <cassert>

Message::Screen::Screen::Screen(quint64 id): Message(id)
{}

Message::Screen::Screen* Message::Screen::Screen::extract(QDataStream& in, quint64 id)
{
    assert(id >= Screen::s_id);
    if(id == GetPosition::s_id) return GetPosition::extract(in, id);
    if(id == SetPosition::s_id) return SetPosition::extract(in, id);
    if(id == SendPosition::s_id) return SendPosition::extract(in, id);

    return new Screen(id);
}

QDataStream& Message::Screen::Screen::serialize(QDataStream& out) const
{
    out << m_id;
    return out;
}
