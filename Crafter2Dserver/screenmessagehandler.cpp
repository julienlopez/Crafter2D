#include "screenmessagehandler.hpp"
#include "client.hpp"
#include "dataaccessor.hpp"
#include "splayer.hpp"

#include <Position>
#include <gPlayer>
#include <Message/Erreur/ErreurServeur>
#include <Message/Screen/SetPosition>
#include <Message/Screen/SendPosition>
#include <Message/Screen/RequestObjectInformation>
#include <Message/Screen/ObjectInformation>
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
    if(message->id() == 5001)
    {
        sendPosition();
        return;
    }
    if(message->id() == Message::Screen::SendPosition::s_id) //mettre à jour la position
    {
        const Message::Screen::SendPosition* m = qobject_cast<const Message::Screen::SendPosition*>(message);
        assert(m);
        m_client->updatePosition(m->position());
        return;
    }
    if(message->id() == Message::Screen::RequestObjectInformation::s_id)
    {
        const Message::Screen::RequestObjectInformation* m = qobject_cast<const Message::Screen::RequestObjectInformation*>(message);
        assert(m);
        WorldElement* e = DataAccessor::getWorldElement(m->code(), m->idPlayer());
        assert(e);
        m_client->send(Message::Screen::ObjectInformation(e));
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
