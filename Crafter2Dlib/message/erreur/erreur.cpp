#include "erreur.hpp"
#include "erreurserveur.hpp"
#include "erreurclient.hpp"
#include "../screen/screen.hpp"

Message::Erreur::Erreur::Erreur(quint64 id, const QString& message): Message(id), m_message(message)
{
    Q_ASSERT(id>=Erreur::s_id && id <5000);
}

QString Message::Erreur::Erreur::message() const
{
    return m_message;
}

Message::Message *Message::Erreur::Erreur::extract(QDataStream& in)
{
    QString mess;
    in >> mess;
    return new Erreur(s_id, mess);
}

QDataStream& Message::Erreur::Erreur::serialize(QDataStream& out) const
{
    out << m_id;
    out << message();
    return out;
}

namespace {

const bool registered = Message::Message::type_factory::instance().registerClasse(Message::Erreur::Erreur::s_id, &Message::Erreur::Erreur::extract);

}
