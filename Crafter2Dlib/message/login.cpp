#include "login.hpp"

Message::Login::Login(QString login, QString mdp, QObject *parent) : Message(Login::s_id, parent), m_login(login), m_mdp(mdp)
{}

QString Message::Login::login() const
{
    return m_login;
}

QString Message::Login::mdp() const
{
    return m_mdp;
}

Message::Message* Message::Login::extract(QDataStream& in)
{
    QString login, mdp;
    in >> login;
    in >> mdp;
    return new Login(login, mdp);
}

QDataStream& Message::Login::serialize(QDataStream& out) const
{
    out << m_id;
    out << m_login;
    out << m_mdp;
    return out;
}

namespace {

const bool registered = Message::Message::type_factory::instance().registerClasse(Message::Login::s_id, &Message::Login::extract);

}

