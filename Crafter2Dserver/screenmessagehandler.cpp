#include "screenmessagehandler.hpp"
#include "client.hpp"
#include "dataaccessor.hpp"

#include <Position>
#include <gPlayer>
#include <Message/Erreur/ErreurServeur>
#include <Message/Screen/SetPosition>
#include <Message/Screen/SendPosition>

#include <QSqlQuery>
#include <QSqlError>

#include <cassert>

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
        return;
    }
    if(message->id() == 5003) //mettre à jour la position
    {
        const Message::Screen::SendPosition* m = qobject_cast<const Message::Screen::SendPosition*>(message);
        assert(m);
        gPlayer* p = DataAccessor::getPlayer(m_client->id());
        p->setPosition(m->position());
        return;
    }

}

void ScreenMessageHandler::sendPosition() const
{
    try
    {
        gPlayer* p = DataAccessor::getPlayer(m_client->id());
        m_client->send(Message::Screen::SetPosition(p->position()));
    }
    catch(DataAccessor::Exception& e)
    {
        m_client->send(Message::Erreur::ErreurServeur(e.message()));
    }
}
