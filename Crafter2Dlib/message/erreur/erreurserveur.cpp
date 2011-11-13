#include "erreurserveur.hpp"
#include "erreurclient.hpp"

#include <cassert>

Message::Erreur::ErreurServeur::ErreurServeur(const QString& message): Erreur(ErreurServeur::s_id, message)
{}

Message::Erreur::ErreurServeur::ErreurServeur(quint64 id, const QString& message): Erreur(id, message)
{
    assert(id>=ErreurServeur::s_id && id < ErreurClient::s_id);
}

Message::Erreur::ErreurServeur* Message::Erreur::ErreurServeur::extract(quint64 id, QDataStream& in)
{
    assert(id>=ErreurServeur::s_id && id <ErreurClient::s_id);
    QString mess;
    in >> mess;

    return new ErreurServeur(id, mess);
}

QDataStream& Message::Erreur::ErreurServeur::serialize(QDataStream& out) const
{
    out << m_id;
    out << message();
    return out;
}
