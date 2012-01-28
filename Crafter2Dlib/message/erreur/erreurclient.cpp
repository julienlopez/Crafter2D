#include "erreurclient.hpp"
#include "../screen/screen.hpp"

Message::Erreur::ErreurClient::ErreurClient(const QString& message): Erreur(ErreurClient::s_id, message)
{}

Message::Erreur::ErreurClient::ErreurClient(quint64 id, const QString& message): Erreur(id, message)
{
    Q_ASSERT(id>=ErreurClient::s_id && id < Screen::Screen::Screen::s_id);
}

Message::Erreur::ErreurClient* Message::Erreur::ErreurClient::extract(quint64 id, QDataStream& in)
{
    Q_ASSERT(id>=ErreurClient::s_id && id < Screen::Screen::s_id);
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
