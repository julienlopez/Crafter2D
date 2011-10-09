#include "screenmessagehandler.hpp"
#include "client.hpp"

#include <Position>
#include <Message/Erreur/ErreurServeur>
#include <Message/Screen/SetPosition>

#include <QSqlQuery>

#include <QDebug>

ScreenMessageHandler::ScreenMessageHandler(Client *parent) :
    QObject(parent), m_client(parent)
{}

void ScreenMessageHandler::traiter(const Message::Message* message) const
{
    if(message->id() < 5000)
    {
        qDebug() << "message invalide!";
        return;
    }

    qDebug() << "ScreenMessageHandler::traiter(" << message->id() << ")";
    if(message->id() == 5001)
    {
        sendPosition();
    }

}

void ScreenMessageHandler::sendPosition() const
{
    QSqlQuery q("SELECT position FROM user WHERE id=" + QString::number(m_client->id()));
    if(!q.exec())
    {
        qDebug() << "impossible d'éxecuter la requete";
        m_client->send(Message::Erreur::ErreurServeur("Impossible d'executer la requetes"));
        return;
    }
    if(q.size() != 1)
    {
        qDebug() << "erreur bd";
        m_client->send(Message::Erreur::ErreurServeur("Erreur de base de données"));
        return;
    }
    q.first();
    Position p(q.value(0).toString());

    if(p.isValid()) qDebug() << p.position();
    else qDebug() << "position invalide";
    m_client->send(Message::Screen::SetPosition(p));
}
