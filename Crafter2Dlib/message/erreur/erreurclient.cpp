#include "erreurclient.hpp"
#include "../screen/screen.hpp"

Message::Erreur::ErreurClient::ErreurClient(const QString& message): Erreur(ErreurClient::s_id, message)
{}

Message::Erreur::ErreurClient::ErreurClient(quint64 id, const QString& message): Erreur(id, message)
{
    Q_ASSERT(id>=ErreurClient::s_id && id < Screen::Screen::Screen::s_id);
}

Message::Message* Message::Erreur::ErreurClient::extract(QDataStream &in)
{
    QString mess;
    in >> mess;

    return new ErreurClient(s_id, mess);
}

QDataStream& Message::Erreur::ErreurClient::serialize(QDataStream& out) const
{
    out << m_id;
    out << message();
    return out;
}

namespace {

const bool registered = Message::Message::type_factory::instance().registerClasse(Message::Erreur::ErreurClient::s_id, &Message::Erreur::ErreurClient::extract);

}
