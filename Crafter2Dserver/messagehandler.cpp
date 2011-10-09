#include "messagehandler.hpp"
#include "client.hpp"

#include <Message/Login>

#include <cassert>

#include <QDebug>

//using namespace std;

MessageHandler::MessageHandler(Client* parent) :
    QObject(parent), m_client(parent)
{}

void MessageHandler::traiter(const Message::Message* message) const
{
    if(message->id() == 1)
    {
        const Message::Login* m = qobject_cast<const Message::Login*>(message);
        assert(m != 0);
        m_client->login(m->login(), m->mdp());
    }
    else //Utils::out << "Données reçues : " << message->id();
         qDebug() << "Données reçues : " << message->id();
}
