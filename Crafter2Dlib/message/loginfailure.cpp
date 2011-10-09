#include "loginfailure.hpp"

Message::LoginFailure::LoginFailure(const QString& erreur): Message(2), m_erreur(erreur)
{}

QString Message::LoginFailure::erreur() const
{
    return m_erreur;
}

Message::LoginFailure* Message::LoginFailure::extract(QDataStream& in)
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
