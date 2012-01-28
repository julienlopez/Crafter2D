#include "localserveur.hpp"
#include "serveur.hpp"

#include <Commande/Shutdown>
#include <Commande/Status>
#include <Commande/StatusUpdate>

#include <QLocalServer>

#include <QDebug>

LocalServeur::LocalServeur(Serveur* parent) :
    QObject(parent), m_socket(0)
{
    m_server = new QLocalServer(this);
    connect(m_server, SIGNAL(newConnection()), this, SLOT(newConnection()));
    m_server->listen("CrafterServer");
}

void LocalServeur::handle(Commande::Commande* commande)
{
    qDebug() << "commande reçue " << commande->id();
    if(commande->id() == Commande::Status::s_id)
    {
        QString str = qobject_cast<Serveur*>(parent())->status();
        qDebug() << "status : " << str;
        send(Commande::StatusUpdate(str));
        return;
    }
    if(commande->id() == Commande::Shutdown::s_id)
    {
        qDebug() << "shutdown";
        qobject_cast<Serveur*>(parent())->shutdown();
        return;
    }
    qDebug() << "commande inconnue " << commande->id();
}

void LocalServeur::newConnection()
{
    if(m_socket == 0)
    {
        m_socket = m_server->nextPendingConnection();

        connect(m_socket, SIGNAL(disconnected()), this, SLOT(onDeconnexion()));
        connect(m_socket, SIGNAL(error(QLocalSocket::LocalSocketError)), this, SLOT(onError(QLocalSocket::LocalSocketError)));
        connect(m_socket, SIGNAL(stateChanged(QLocalSocket::LocalSocketState)), this, SLOT(onStateChanged(QLocalSocket::LocalSocketState)));
        connect(m_socket, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
        return;
    }

    QLocalSocket* s = m_server->nextPendingConnection();
    s->close();
}

void LocalServeur::onDeconnexion()
{
    qDebug() << "déconnexion de la commande";
    m_socket->deleteLater();
    m_socket = 0;
}

void LocalServeur::onError(QLocalSocket::LocalSocketError socketError)
{
    qDebug() << "error: " << socketError << " => ";
    if(m_socket != 0) qDebug() << m_socket->errorString();
    qDebug() << m_server->serverError() << " => ";
    qDebug() << m_server->errorString();
}

void LocalServeur::onStateChanged(QLocalSocket::LocalSocketState socketState)
{
    qDebug() << "state changed: " << socketState;
}

void LocalServeur::send(const Commande::Commande& commande)
{
    qDebug() << "LocalServeur::send(" << commande.id() << ")";
    QByteArray paquet;
    //paquet.clear();
    QDataStream out(&paquet, QIODevice::WriteOnly);

    //out << (quint16) 0; // On écrit 0 au début du paquet pour réserver la place pour écrire la taille
    commande.serialize(out); // On ajoute le message à la suite
    //qDebug() << "paquet = " << QString(paquet);
    out.device()->seek(0); // On se replace au début du paquet
    //qDebug() << "paquet.size() = " << paquet.size();
    //qDebug() << "paquet = " << QString(paquet);
    out << (quint16) (paquet.size() - sizeof(quint16)); // On écrase le 0 qu'on avait réservé par la longueur du message
    write(paquet);
}

void LocalServeur::write(const QByteArray& paquet)
{
    //qDebug() << "LocalServeur::write(" << QString(paquet) << ")";
    if(m_socket != 0) m_socket->write(paquet);
    else qDebug() << "aucun socket connecté";
}

void LocalServeur::donneesRecues()
{
    QDataStream in(m_socket);
    if(tailleMessage == 0)
    {
        if (m_socket->bytesAvailable() < (int)sizeof(quint16)) return;
        in >> tailleMessage;
    }
    if (m_socket->bytesAvailable() < tailleMessage) return;

    Commande::Commande* commande = Commande::Commande::extract(in);
    qDebug() << commande->id();
    handle(commande);
    commande->deleteLater();
    tailleMessage = 0;
}
