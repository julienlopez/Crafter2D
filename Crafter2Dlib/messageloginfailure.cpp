#include "messageloginfailure.hpp"

MessageLoginFailure::MessageLoginFailure(const QString& erreur): Message(2), m_erreur(erreur)
{}

QString MessageLoginFailure::erreur() const
{
    return m_erreur;
}

MessageLoginFailure* MessageLoginFailure::extract(QDataStream& in)
{
    QString erreur;
    in >> erreur;
    return new MessageLoginFailure(erreur);
}

QDataStream& MessageLoginFailure::serialize(QDataStream& out) const
{
    out << m_id;
    out << m_erreur;
    return out;
}
