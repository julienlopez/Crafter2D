#include "screenmessagehandler.hpp"
#include "client.hpp"
#include "dataaccessor.hpp"
#include "splayer.hpp"

#include <Position>
#include <gPlayer>
#include <Message/Erreur/ErreurServeur>
#include <Message/Screen/GetPosition>
#include <Message/Screen/SetPosition>
#include <Message/Screen/SendPosition>
#include <Message/Screen/RequestObjectInformation>
#include <Message/Screen/ObjectInformation>
#include <Message/Screen/GetNearbyObjects>
#include <Message/Screen/NearbyObjects>

#include <QSqlQuery>
#include <QSqlError>

#include <QDebug>

ScreenMessageHandler::ScreenMessageHandler(Client *parent) :
    QObject(parent), m_client(parent)
{}

void ScreenMessageHandler::traiter(const Message::Message* message) const
{
    if(message->id() < Message::Screen::Screen::s_id)
    {
        qDebug() << "message invalide!";
        return;
    }
    if(message->id() == Message::Screen::GetPosition::s_id)
    {
        sendPosition();
        return;
    }
    if(message->id() == Message::Screen::SendPosition::s_id) //mettre à jour la position
    {
        const Message::Screen::SendPosition* m = qobject_cast<const Message::Screen::SendPosition*>(message);
        Q_ASSERT(m);
        m_client->updatePosition(m->position());
        return;
    }
    if(message->id() == Message::Screen::RequestObjectInformation::s_id)
    {
        const Message::Screen::RequestObjectInformation* m = qobject_cast<const Message::Screen::RequestObjectInformation*>(message);
        Q_ASSERT(m);
        WorldElement* e = DataAccessor::getWorldElement(m->code(), m->idPlayer());
        Q_ASSERT(e);
        m_client->send(Message::Screen::ObjectInformation(e));
        return;
    }
    if(message->id() == Message::Screen::GetNearbyObjects::s_id)
    {
        const Message::Screen::GetNearbyObjects* m = qobject_cast<const Message::Screen::GetNearbyObjects*>(message);
        Q_ASSERT(m);
        qDebug() << "GetNearbyObjects: " << m->position().position();
        QList<quint64> staticObjects = DataAccessor::getNearbyStaticObjects(m->position(), m->distance());
        Message::Screen::NearbyObjects mess;
        mess.setStaticObjects(staticObjects);
        m_client->send(mess);
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
