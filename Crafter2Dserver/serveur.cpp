#include "serveur.hpp"
#include "client.hpp"

#include <Utils>

#include <cassert>

#include <QTcpServer>
#include <QTcpSocket>

#include <QSqlDatabase>
#include <QStringList>

#include <QDebug>

Serveur::Serveur(QObject *parent) :
    QObject(parent)
{
    serveur = new QTcpServer(this);
}

bool Serveur::start()
{
    if(!QSqlDatabase::drivers().contains("QMYSQL"))
    {
        qDebug() << "Impossible de charger le plugin mysql!!";
        return false;
    }

    if (!serveur->listen(QHostAddress::Any, 50885))
    {
        /*Utils::out*/ qDebug() << "Le serveur n'a pas pu être démarré. Raison :\n" << serveur->errorString();
        return false;
    }
//    Utils::out << "serveur démarré\n" << endl;
    qDebug() << "serveur démarré";

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("crafter");
    db.setUserName("root");
    db.setPassword("");
    if(db.open()) qDebug() << "Base de donnée ouverte";
    else
    {
        qDebug() << "Impossible de se connecter à la base de données";
        return false;
    }

    connect(serveur, SIGNAL(newConnection()), this, SLOT(nouvelleConnexion()));
    return true;
}

void Serveur::envoyerATous(const Message::Message& message)
{
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    out << (quint16) 0; // On écrit 0 au début du paquet pour réserver la place pour écrire la taille
    message.serialize(out); // On ajoute le message à la suite
    out.device()->seek(0); // On se replace au début du paquet
    out << (quint16) (paquet.size() - sizeof(quint16)); // On écrase le 0 qu'on avait réservé par la longueur du message
    for(int i = 0; i<clients.size(); i++)
    {
        clients.at(i)->write(paquet);
    }
}

void Serveur::nouvelleConnexion()
{
//    Utils::out << "Un nouveau client vient de se connecter";
    qDebug() << "Un nouveau client vient de se connecter";

    QTcpSocket* socket = serveur->nextPendingConnection();
    Client* nouveauClient = new Client(socket, this);
    clients << nouveauClient;
    connect(nouveauClient, SIGNAL(disconnected()), this, SLOT(deconnexionClient()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSocketError(QAbstractSocket::SocketError)));
}

void Serveur::deconnexionClient()
{
//    Utils::out << "déconnexion client";
    qDebug() << "déconnexion client";

    Client* client = qobject_cast<Client*>(sender());
    assert(client != 0);
    clients.removeOne(client);
    client->deleteLater();
}

void Serveur::onSocketError(QAbstractSocket::SocketError err)
{
//    Utils::out << "SocketError: " << err;
    qDebug() << "SocketError: " << err;
}
