#include "messagehandler.hpp"
#include "client.hpp"

#include <MessageLogin>

#include <cassert>

#include <QDebug>

//using namespace std;

MessageHandler::MessageHandler(Client* parent) :
    QObject(parent), m_client(parent)
{}

void MessageHandler::traiter(const Message* message) const
{
    if(message->id() == 1)
    {
        const MessageLogin* m = qobject_cast<const MessageLogin*>(message);
        assert(m != 0);
        m_client->login(m->login(), m->mdp());
    }
    else //Utils::out << "Données reçues : " << message->id();
         qDebug() << "Données reçues : " << message->id();
}
