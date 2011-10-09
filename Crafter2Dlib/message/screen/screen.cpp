#include "screen.hpp"
#include "getposition.hpp"

#include <cassert>

Message::Screen::Screen::Screen(quint64 id): Message(id)
{}

Message::Screen::Screen* Message::Screen::Screen::extract(QDataStream& in, quint64 id)
{
    assert(id >= 5000);
    if(id == 5001) return GetPosition::extract(in, id);

    return new Screen(id);
}

QDataStream& Message::Screen::Screen::serialize(QDataStream& out) const
{
    out << m_id;
    return out;
}
