#include "message.hpp"
#include "messagelogin.hpp"
#include "messageloginfailure.hpp"

Message::Message(quint64 id, QObject *parent) :
    QObject(parent), m_id(id)
{}

Message::Message(const Message& m): QObject(m.parent()), m_id(m.m_id)
{}

quint64 Message::id() const
{
    return m_id;
}

Message* Message::extract(QDataStream& in)
{
    quint64 id;
    in >> id;
    if(id == 1) return MessageLogin::extract(in);
    if(id == 2) return MessageLoginFailure::extract(in);
    return new Message(id);
}

QDataStream& Message::serialize(QDataStream& out) const
{
    out << m_id;
    return out;
}
