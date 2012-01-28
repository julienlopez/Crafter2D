#include "cmd.hpp"

#include <Commande/Shutdown>
#include <Commande/Status>
#include <Commande/StatusUpdate>

#include <QCoreApplication>

#include <QDebug>

Cmd::Cmd(QObject *parent) :
    QObject(parent), boucle(true), tailleMessage(0), out(stdout, QIODevice::WriteOnly), in(stdin, QIODevice::ReadOnly)
{
    m_socket = new QLocalSocket(this);
    connect(m_socket, SIGNAL(connected()), this, SLOT(onConnexion()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(onDeconnexion()));
    connect(m_socket, SIGNAL(error(QLocalSocket::LocalSocketError)), this, SLOT(onError(QLocalSocket::LocalSocketError)));
    connect(m_socket, SIGNAL(stateChanged(QLocalSocket::LocalSocketState)), this, SLOT(onStateChanged(QLocalSocket::LocalSocketState)));
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
    m_socket->connectToServer("CrafterServer");
    out << tr("demarrage\n");

    connect(this, SIGNAL(quit()), qApp, SLOT(quit()));
}

void Cmd::start()
{
    qDebug() << "console prete";
    QString ligne;
    while(boucle)
    {
        ligne = in.readLine();
        process(ligne);
    }
}

void Cmd::handle(Commande::Commande* commande)
{
    qDebug() << "commande reçue " << commande->id();
    if(commande->id() == 3)
    {
        Commande::StatusUpdate* s = qobject_cast<Commande::StatusUpdate*>(commande);
        qDebug() << s->message();
        return;
    }
    qDebug() << "commande inconnue " << commande->id();
}

void Cmd::process(QString str)
{
    if(str == "shutdown")
    {
        send(Commande::Shutdown());
        return;
    }
    if(str == "status")
    {
        send(Commande::Status());
        qDebug() << m_socket->state();
        return;
    }
    if(str == "exit")
    {
        m_socket->close();
        emit quit();
        return;
    }
    qDebug() << "commande inconnue:" << str;
}

void Cmd::onConnexion()
{
    qDebug() << "connexion";
}

void Cmd::onDeconnexion()
{
    qDebug() << "déconnexion";
}

void Cmd::onError(QLocalSocket::LocalSocketError socketError)
{
    qDebug() << "error: " << socketError;
    if(socketError == QLocalSocket::ServerNotFoundError)
    {
        qDebug() << "impossible de se connecter au serveur";
        emit quit(); //qApp->quit();//exit();
        return;
    }
    qDebug() << m_socket->errorString();
}

void Cmd::onStateChanged(QLocalSocket::LocalSocketState socketState)
{
    if(socketState == QLocalSocket::ConnectingState)
    {
        qDebug()  << "connexion en cours";
        return;
    }
    if(socketState == QLocalSocket::ConnectedState)
    {
        qDebug()  << "connecté";
        Cmd::start();
        return;
    }

    qDebug() << "state changed: " << socketState;
}

void Cmd::send(const Commande::Commande& commande)
{
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    out << (quint16) 0; // On écrit 0 au début du paquet pour réserver la place pour écrire la taille
    commande.serialize(out); // On ajoute le message à la suite
    out.device()->seek(0); // On se replace au début du paquet
    out << (quint16) (paquet.size() - sizeof(quint16)); // On écrase le 0 qu'on avait réservé par la longueur du message
    write(paquet);
}

void Cmd::write(const QByteArray& paquet)
{
    m_socket->write(paquet);
}

void Cmd::donneesRecues()
{
    qDebug() << "Client::donneesRecues()";
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
