#include "login.hpp"

namespace Message {

Login::Login(QString login, QString mdp, QObject *parent) : Message(1, parent), m_login(login), m_mdp(mdp)
{}

QString Login::login() const
{
    return m_login;
}

QString Login::mdp() const
{
    return m_mdp;
}

Login* Login::extract(QDataStream& in)
{
    QString login, mdp;
    in >> login;
    in >> mdp;
    return new Login(login, mdp);
}

QDataStream& Login::serialize(QDataStream& out) const
{
    out << m_id;
    out << m_login;
    out << m_mdp;
    return out;
}

}
