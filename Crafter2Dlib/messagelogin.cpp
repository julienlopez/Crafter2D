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

QDataStream& operator << (QDataStream& out, const MessageLogin& m)
{
    out << m.m_id;
    out << m.m_login;
    out << m.m_mdp;
    return out;
}

QDataStream& operator >> (QDataStream& in, MessageLogin& m)
{
    in >> m.m_id;
    in >> m.m_login;
    in >> m.m_mdp;
    return in;
}
