#include "serveur.hpp"
#include "client.hpp"
#include "sutils.hpp"
#include "dataaccessor.hpp"
#include "localserveur.hpp"
#include "splayer.hpp"

#include <Utils>
#include <Message/Screen/SendPosition>
#include <Message/Screen/MajPosition>

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
    //connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(onQuit()));

    m_savingTimer = new QTimer(this);
    connect(m_savingTimer, SIGNAL(timeout()), &DataAccessor::instance(), SLOT(processSavingQueue()));
    m_savingTimer->start(10000);

    m_updatePosTimer = new QTimer(this);
    connect(m_updatePosTimer, SIGNAL(timeout()), this, SLOT(updatePosition()));
    m_updatePosTimer->start(100);

    m_localServeur = new LocalServeur(this);
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

QString Serveur::status() const
{
    QString res;
    res += "server status:\n";
    res += QString::number(clients.size()) + " clients connectés\n";
    return res;
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
    QTcpSocket* socket = serveur->nextPendingConnection();
    Client* nouveauClient = new Client(socket, this);
    clients << nouveauClient;
    connect(nouveauClient, SIGNAL(disconnected()), this, SLOT(deconnexionClient()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSocketError(QAbstractSocket::SocketError)));
}

void Serveur::deconnexionClient()
{
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

/*
void Serveur::onQuit()
{
    qDebug() << "onQuit()";
    DataAccessor::instance().clearAll();
    DataAccessor::instance().processSavingQueue();
}

void Serveur::onClientUpdatePosition(quint64 id, const Position& pos)
{
    qDebug() << "pos update " << id << " => " << pos.position();
    Client* c;
    foreach(c, clients)
    {
        if(c->id() == id) continue;
    }
}*/

void Serveur::updatePosition()
{
    //TODO optimiser l'echange des positions entre joueurs;
    Client* c, *cl;
    Position pos;
    foreach(c, clients)
    {
        foreach(cl, clients)
        {
            if(c == cl || !c || !cl) continue;
            if(!c->player() || !cl->player()) continue;
            pos = c->player()->position();
            if((c->player()->position().position() - cl->player()->position().position()).manhattanLength() < 50)
                c->send(Message::Screen::MajPosition(cl->player()));
        }
    }
}

void Serveur::shutdown()
{
    qDebug() << "shuting down";
    DataAccessor::instance().clearAll();
    DataAccessor::instance().processSavingQueue();
    deleteLater();
}
