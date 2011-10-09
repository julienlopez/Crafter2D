#include "erreurclient.hpp"

#include <cassert>

Message::Erreur::ErreurClient::ErreurClient(const QString& message): Erreur(3000, message)
{}

Message::Erreur::ErreurClient::ErreurClient(quint64 id, const QString& message): Erreur(id, message)
{
    assert(id>=3000 && id <5000);
}

Message::Erreur::ErreurClient* Message::Erreur::ErreurClient::extract(quint64 id, QDataStream& in)
{
    assert(id>=3000 && id <5000);
    QString mess;
    in >> mess;

    return new ErreurClient(id, mess);
}

QDataStream& Message::Erreur::ErreurClient::serialize(QDataStream& out) const
{
    out << m_id;
    out << message();
    return out;
}
