#include "erreurserveur.hpp"

#include <cassert>

Message::Erreur::ErreurServeur::ErreurServeur(const QString& message): Erreur(1000, message)
{}

Message::Erreur::ErreurServeur::ErreurServeur(quint64 id, const QString& message): Erreur(id, message)
{
    assert(id>=1000 && id <3000);
}

Message::Erreur::ErreurServeur* Message::Erreur::ErreurServeur::extract(quint64 id, QDataStream& in)
{
    assert(id>=1000 && id <3000);
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
