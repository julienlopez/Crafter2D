#include "client.hpp"

#include <Utils>

#include <cassert>

#include <QTcpSocket>

Client::Client(QTcpSocket* socket, QObject* parent) :
    QObject(parent), m_socket(socket), tailleMessage(0)
{
    connect(socket, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
    connect(socket, SIGNAL(disconnected()), this, SIGNAL(disconnected()));
}

void Client::send(const Message& message)
{
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    out << (quint16) 0; // On �crit 0 au d�but du paquet pour r�server la place pour �crire la taille
    out << message; // On ajoute le message � la suite
    out.device()->seek(0); // On se replace au d�but du paquet
    out << (quint16) (paquet.size() - sizeof(quint16)); // On �crase le 0 qu'on avait r�serv� par la longueur du message
    write(paquet);
}

void Client::write(const QByteArray& paquet)
{
    m_socket->write(paquet);
}

void Client::donneesRecues()
{
    assert(m_socket == sender());
    QDataStream in(m_socket);
    if(tailleMessage == 0) // Si on ne conna�t pas encore la taille du message, on essaie de la r�cup�rer
    {
        if (m_socket->bytesAvailable() < (int)sizeof(quint16)) // On n'a pas re�u la taille du message en entier
             return;
        in >> tailleMessage; // Si on a re�u la taille du message en entier, on la r�cup�re
    }
    // Si on conna�t la taille du message, on v�rifie si on a re�u le message en entier
    if (m_socket->bytesAvailable() < tailleMessage) return;

    // Si ces lignes s'ex�cutent, c'est qu'on a re�u tout le message : on peut le r�cup�rer !
    Message message;
    in >> message;

    Utils::out << "Donn�es re�ues : " << message.id();
}
