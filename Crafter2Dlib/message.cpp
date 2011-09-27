#include "message.hpp"

Message::Message(quint64 id, QObject *parent) :
    QObject(parent), m_id(id)
{}

Message::Message(const Message& m): QObject(m.parent()), m_id(m.id())
{}

quint64 Message::id() const
{
    return m_id;
}

QDataStream& operator << (QDataStream& out, const Message& m)
{
    out << m.m_id;
    return out;
}

QDataStream& operator >> (QDataStream& in, Message& m)
{
    quint64 id;
    in >> id;
    if(id == 0) m.m_id = id;
    else if(id == 1)
    {

    }
    return in;
}
