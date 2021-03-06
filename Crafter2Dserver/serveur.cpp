#include "serveur.hpp"
#include "client.hpp"
#include "sutils.hpp"
#include "dataaccessor.hpp"
#include "localserveur.hpp"
#include "splayer.hpp"

#include <Message/Screen/SendPosition>
#include <Message/Screen/MajPosition>

#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QSqlDatabase>
#include <QStringList>
#include <QTimer>
#include <QSqlQuery>

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

    qDebug() << "chargement des objets";
    loadObjects();

    connect(serveur, SIGNAL(newConnection()), this, SLOT(nouvelleConnexion()));
    qDebug() << "serveur pret";
    return true;
}

QString Serveur::status() const
{
    QString res;
    /*res += "server status:\n";
    res += QString::number(clients.size()) + " clients connect�s\n";*/
    res += "server status: ";
    res += QString::number(clients.size()) + " clients connectes";

    return res;
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

void Serveur::loadObjects()
{
    //statics objects
    QSqlQuery query("SELECT id FROM staticobject");
    if(!query.exec()) qDebug() << "Impossible d'executer la requetes";
    while(query.next()) {
        quint64 id = query.value(0).toUInt();
        try
        {
            DataAccessor::getStaticObject(id);
        }
        catch(DataAccessor::Exception& ex)
        {
            qDebug() << "Impossible de charger le staticobject " << id << ": " << ex.message();
        }
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
    Q_ASSERT(client != 0);
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

#include <typeinfo>

void Serveur::updatePosition()
{
    //TODO optimiser l'echange des positions entre joueurs;
    Client* c, *cl;
    Position pos;
    foreach(c, clients)
    {
        Q_ASSERT(c);
        foreach(cl, clients)
        {
            Q_ASSERT(cl);
            if(c == cl || !c->player() || !cl->player()) continue;
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
