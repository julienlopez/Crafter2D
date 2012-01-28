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

Message::Erreur::Erreur* Message::Erreur::Erreur::extract(quint64 id, QDataStream& in)
{
    Q_ASSERT(id>=Erreur::s_id && id < Screen::Screen::s_id);

    if(id>=ErreurServeur::s_id && id <ErreurClient::s_id) return ErreurServeur::extract(id, in);
    if(id>=ErreurClient::s_id && id < Screen::Screen::s_id) return ErreurClient::extract(id, in);

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
