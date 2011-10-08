#include "client.hpp"
#include "messagehandler.hpp"

#include <MessageLoginFailure>
#include <MessageLoginSuccess>

#include <cassert>

#include <QTcpSocket>
#include <QSqlQuery>
#include <QSqlError>

#include <QDebug>

Client::Client(QTcpSocket* socket, QObject* parent) :
    QObject(parent), m_socket(socket), tailleMessage(0)
{
    messageHandler = new MessageHandler(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
    connect(socket, SIGNAL(disconnected()), this, SIGNAL(disconnected()));
}

void Client::send(const Message& message)
{
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    out << (quint16) 0; // On écrit 0 au début du paquet pour réserver la place pour écrire la taille
    message.serialize(out); // On ajoute le message à la suite
    out.device()->seek(0); // On se replace au début du paquet
    out << (quint16) (paquet.size() - sizeof(quint16)); // On écrase le 0 qu'on avait réservé par la longueur du message
    write(paquet);
}

void Client::write(const QByteArray& paquet)
{
    m_socket->write(paquet);
}

void Client::login(const QString& login, const QString& mdp)
{
    QSqlQuery query;
    query.prepare("SELECT id FROM user WHERE pseudo = :login AND mdp = :mdp");
    query.bindValue(":login", login);
    query.bindValue(":mdp", mdp);
    qDebug() << query.executedQuery();
    if(!query.exec())
    {
        qDebug() << "impossible d'executer la requete de login" << query.lastError().text();
        send(MessageLoginFailure("Erreur serveur"));
        return;
    }

    if(query.size() != 1)
    {
        send(MessageLoginFailure("Informations de login incorrectes"));
        return;
    }
    send(MessageLoginSuccess());
}

void Client::donneesRecues()
{
    assert(m_socket == sender());
    QDataStream in(m_socket);
    if(tailleMessage == 0)
    {
        if (m_socket->bytesAvailable() < (int)sizeof(quint16)) return;
        in >> tailleMessage;
    }
    if (m_socket->bytesAvailable() < tailleMessage) return;

    // Si ces lignes s'exécutent, c'est qu'on a reçu tout le message : on peut le récupérer !
    Message* message = Message::extract(in);
    messageHandler->traiter(message);
    message->deleteLater();
}
