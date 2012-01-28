#include "messagehandler.hpp"
#include "client.hpp"
#include "screenmessagehandler.hpp"

#include <Message/Login>
#include <QDebug>

MessageHandler::MessageHandler(Client* parent) :
    QObject(parent), m_client(parent)
{
    screenMessageHandler = new ScreenMessageHandler(parent);
}

void MessageHandler::traiter(const Message::Message* message) const
{
    if(message->id() == 1)
    {
        const Message::Login* m = qobject_cast<const Message::Login*>(message);
        Q_ASSERT(m != 0);
        m_client->login(m->login(), m->mdp());
    }
    else if(message->id() >= 5000) screenMessageHandler->traiter(message);
    else qDebug() << "Données reçues : " << message->id();
}
