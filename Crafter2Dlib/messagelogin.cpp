#include "messagelogin.hpp"

MessageLogin::MessageLogin(QString login, QString mdp, QObject *parent) : Message(1, parent), m_login(login), m_mdp(mdp)
{}

QString MessageLogin::login() const
{
    return m_login;
}

QString MessageLogin::mdp() const
{
    return m_mdp;
}

MessageLogin* MessageLogin::extract(QDataStream& in)
{
    QString login, mdp;
    in >> login;
    in >> mdp;
    return new MessageLogin(login, mdp);
}

QDataStream& MessageLogin::serialize(QDataStream& out) const
{
    out << m_id;
    out << m_login;
    out << m_mdp;
    return out;
}
