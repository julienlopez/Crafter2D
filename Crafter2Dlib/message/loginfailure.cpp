#include "loginfailure.hpp"

Message::LoginFailure::LoginFailure(const QString& erreur): Message(LoginFailure::s_id), m_erreur(erreur)
{}

QString Message::LoginFailure::erreur() const
{
    return m_erreur;
}

Message::Message *Message::LoginFailure::extract(QDataStream& in)
{
    QString erreur;
    in >> erreur;
    return new LoginFailure(erreur);
}

QDataStream& Message::LoginFailure::serialize(QDataStream& out) const
{
    out << m_id;
    out << m_erreur;
    return out;
}

namespace {

const bool registered = Message::Message::type_factory::instance().registerClasse(Message::LoginFailure::s_id, &Message::LoginFailure::extract);

}
