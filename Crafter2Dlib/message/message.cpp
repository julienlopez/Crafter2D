#include "message.hpp"
#include "login.hpp"
#include "loginfailure.hpp"
#include "loginsuccess.hpp"
#include "erreur/erreur.hpp"
#include "screen/screen.hpp"

Message::Message::Message(quint64 id, QObject *parent) :
    QObject(parent), m_id(id)
{}

Message::Message::Message(const Message& m): QObject(m.parent()), m_id(m.m_id)
{}

quint64 Message::Message::id() const
{
    return m_id;
}

Message::Message* Message::Message::extract(QDataStream& in)
{
    quint64 id;
    in >> id;
    return type_factory::instance().creer(id, in);
}

QDataStream& Message::Message::serialize(QDataStream& out) const
{
    out << m_id;
    return out;
}
