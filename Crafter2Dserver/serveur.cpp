#include "serveur.hpp"
#include "client.hpp"
#include "sutils.hpp"
#include "dataaccessor.hpp"

#include <Utils>

#include <cassert>

#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QSqlDatabase>
#include <QStringList>
#include <QTimer>

#include <QDebug>

Serveur::Serveur(QObject *parent) :
    QObject(parent)
{
    serveur = new QTcpServer(this);
    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(onQuit()));

    m_savingTimer = new QTimer(this);
    connect(m_savingTimer, SIGNAL(timeout()), &DataAccessor::instance(), SLOT(processSavingQueue()));
    m_savingTimer->start(10000);
}

bool Serveur::start()
{
    if(!QSqlDatabase::drivers().contains("QMYSQL"))
    {
        qDebug() << "Impossible de charger le plugin mysql!!";
        qDebug() << "plugins dispo: " << QSqlDatabase::drivers();
        return false;
    }

    if (!serveur->listen(QHostAddress::Any, 50885))
    {
        /*Utils::out*/ qDebug() << "Le serveur n'a pas pu �tre d�marr�. Raison :\n" << serveur->errorString();
        return false;
    }
//    Utils::out << "serveur d�marr�\n" << endl;
    qDebug() << "serveur d�marr�";

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("crafter");
    db.setUserName("root");
    db.setPassword("");
    if(db.open()) qDebug() << "Base de donn�e ouverte";
    else
    {
        qDebug() << "Impossible de se connecter � la base de donn�es";
        return false;
    }

    connect(serveur, SIGNAL(newConnection()), this, SLOT(nouvelleConnexion()));
    return true;
}

void Serveur::envoyerATous(const Message::Message& message)
{
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    out << (quint16) 0; // On �crit 0 au d�but du paquet pour r�server la place pour �crire la taille
    message.serialize(out); // On ajoute le message � la suite
    out.device()->seek(0); // On se replace au d�but du paquet
    out << (quint16) (paquet.size() - sizeof(quint16)); // On �crase le 0 qu'on avait r�serv� par la longueur du message
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

    SUtils::log() << "serveur d�marr�\n";
}

void Serveur::deconnexionClient()
{
//    Utils::out << "d�connexion client";
    qDebug() << "d�connexion client";

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

void Serveur::onQuit()
{
    qDebug() << "onQuit()";
    DataAccessor::instance().processSavingQueue();
}
