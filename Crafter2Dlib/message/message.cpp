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
    if(id == Login::s_id) return Login::extract(in);
    if(id == LoginFailure::s_id) return LoginFailure::extract(in);
    if(id == LoginSuccess::s_id) return LoginSuccess::extract(in);

    if(id >= Erreur::Erreur::s_id && id < Screen::Screen::s_id) return Erreur::Erreur::extract(id, in); //TODO mettre les extract dans le même ordre

    if(id >= Screen::Screen::s_id) return Screen::Screen::extract(in, id);

    return new Message(id);
}

QDataStream& Message::Message::serialize(QDataStream& out) const
{
    out << m_id;
    return out;
}

