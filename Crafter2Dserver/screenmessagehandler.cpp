#include "screenmessagehandler.hpp"
#include "client.hpp"
#include "dataaccessor.hpp"

#include <Position>
#include <gPlayer>
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
