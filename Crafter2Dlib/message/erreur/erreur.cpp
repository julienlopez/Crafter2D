#include "erreur.hpp"
#include "erreurserveur.hpp"
#include "erreurclient.hpp"

#include <cassert>

Message::Erreur::Erreur::Erreur(quint64 id, const QString& message): Message(id), m_message(message)
{
    assert(id>=1000 && id <5000);
}

QString Message::Erreur::Erreur::message() const
{
    return m_message;
}

Message::Erreur::Erreur* Message::Erreur::Erreur::extract(quint64 id, QDataStream& in)
{
    assert(id>=1000 && id <5000);

    if(id>=1000 && id <3000) return ErreurServeur::extract(id, in);
    if(id>=3000 && id <5000) return ErreurClient::extract(id, in);

    QString mess;
    in >> mess;
    return new Erreur(id, mess);
}

QDataStream& Message::Erreur::Erreur::serialize(QDataStream& out) const
{
    out << m_id;
    out << message();
    return out;
}
