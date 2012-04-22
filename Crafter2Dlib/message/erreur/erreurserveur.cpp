#include "erreurserveur.hpp"
#include "erreurclient.hpp"

Message::Erreur::ErreurServeur::ErreurServeur(const QString& message): Erreur(ErreurServeur::s_id, message)
{}

Message::Erreur::ErreurServeur::ErreurServeur(quint64 id, const QString& message): Erreur(id, message)
{
    Q_ASSERT(id>=ErreurServeur::s_id && id < ErreurClient::s_id);
}

Message::Message* Message::Erreur::ErreurServeur::extract(QDataStream &in)
{
    QString mess;
    in >> mess;

    return new ErreurServeur(s_id, mess);
}

QDataStream& Message::Erreur::ErreurServeur::serialize(QDataStream& out) const
{
    out << m_id;
    out << message();
    return out;
}

namespace {

const bool registered = Message::Message::type_factory::instance().registerClasse(Message::Erreur::ErreurClient::s_id, &Message::Erreur::ErreurClient::extract);

}
