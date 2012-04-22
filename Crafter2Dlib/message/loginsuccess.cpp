#include "loginsuccess.hpp"

Message::LoginSuccess::LoginSuccess(quint64 idPlayer): Message(LoginSuccess::s_id), m_idPlayer(idPlayer)
{}

quint64 Message::LoginSuccess::idPlayer() const
{
    return m_idPlayer;
}

Message::Message *Message::LoginSuccess::extract(QDataStream& in)
{
    quint64 idPlayer;
    in >> idPlayer;
    return new LoginSuccess(idPlayer);
}

QDataStream& Message::LoginSuccess::serialize(QDataStream& out) const
{
    out << m_id;
    out << m_idPlayer;
    return out;
}

namespace {

const bool registered = Message::Message::type_factory::instance().registerClasse(Message::LoginSuccess::s_id, &Message::LoginSuccess::extract);

}
