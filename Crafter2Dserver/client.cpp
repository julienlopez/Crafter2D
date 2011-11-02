#include "client.hpp"
#include "messagehandler.hpp"
#include "dataaccessor.hpp"
#include "splayer.hpp"

#include <Message/LoginFailure>
#include <Message/LoginSuccess>

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

Client::~Client()
{
    DataAccessor::instance().saveSlot(static_cast<sPlayer*>(DataAccessor::getPlayer(id())));
}

void Client::send(const Message::Message& message)
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
    if(!query.exec())
    {
        qDebug() << "impossible d'executer la requete de login" << query.lastError().text();
        send(Message::LoginFailure("Erreur serveur"));
        return;
    }

    if(query.size() != 1)
    {
        send(Message::LoginFailure("Informations de login incorrectes"));
        return;
    }

    setPseudo(login);
    query.first();
    setId(query.value(0).toULongLong());
    send(Message::LoginSuccess());
}

void Client::donneesRecues()
{
    assert(m_socket == sender());
//    qDebug() << "Client::donneesRecues()";
    QDataStream in(m_socket);
    if(tailleMessage == 0)
    {
        if (m_socket->bytesAvailable() < (int)sizeof(quint16)) return;
        in >> tailleMessage;
    }
    if (m_socket->bytesAvailable() < tailleMessage) return;

    Message::Message* message = Message::Message::extract(in);
//    qDebug() << message->id();
    messageHandler->traiter(message);
    message->deleteLater();
    tailleMessage = 0;
}
