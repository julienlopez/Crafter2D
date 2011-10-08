#include "mainwindow.hpp"
#include "loginwidget.hpp"

#include <MessageLogin>
#include <MessageLoginFailure>
#include <MessageLoginSuccess>

#include <QTcpSocket>
#include <QMessageBox>
#include <QLabel>

#include <QDebug>

#include <cassert>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), tailleMessage(0)
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
    connect(socket, SIGNAL(connected()), this, SLOT(connecte()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(deconnecte()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(erreurSocket(QAbstractSocket::SocketError)));
    connect(this, SIGNAL(messageRecu(Message*)), this, SLOT(onNewMessage(Message*)));

    setCentralWidget(new QLabel(tr("Connexion au serveur...")));
    socket->connectToHost("127.0.0.1", 50885);
}

MainWindow::~MainWindow()
{}

void MainWindow::send(const Message& message)
{
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    out << (quint16) 0;
    message.serialize(out);
    out.device()->seek(0);
    out << (quint16) (paquet.size() - sizeof(quint16));
    socket->write(paquet);
}

void MainWindow::donneesRecues()
{
    QDataStream in(socket);
    if (tailleMessage == 0)
    {
        if (socket->bytesAvailable() < (int)sizeof(quint16)) return;
        in >> tailleMessage;
    }
    if (socket->bytesAvailable() < tailleMessage) return;

    Message* message = Message::extract(in);
    emit messageRecu(message);

    tailleMessage = 0;
}

void MainWindow::connecte()
{
    centralWidget()->deleteLater();
    LoginWidget* lw = new LoginWidget;
    connect(lw, SIGNAL(sendLogin(QString,QString)), this, SLOT(sendLogin(QString, QString)));
    setCentralWidget(lw);
}

void MainWindow::deconnecte()
{

}

void MainWindow::erreurSocket(QAbstractSocket::SocketError e)
{
    static QString erreur = "Erreur r�seau";
    switch(e)
    {
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::warning(this, erreur, "le serveur n'a pas pu �tre trouv�.");
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::warning(this, erreur, "le serveur a refus� la connexion.");
        break;
    case QAbstractSocket::RemoteHostClosedError:
        QMessageBox::warning(this, erreur, "le serveur a coup� la connexion.");
        break;
    default:
        QMessageBox::warning(this, erreur, "ERREUR : ") + socket->errorString();
    }
}

void MainWindow::sendLogin(QString login, QString mdp)
{
    qDebug() << "sendLogin(" << login << "," << mdp << ")";
    send(MessageLogin(login, mdp));
    QWidget* w = new QWidget;
    QWidget* l = centralWidget();
    setCentralWidget(w);
    l->deleteLater();
}

void MainWindow::onNewMessage(Message* message)
{
    if(message->id() == 2)
    {
        const MessageLoginFailure* m = qobject_cast<const MessageLoginFailure*>(message);
        assert(m != 0);
        QMessageBox::information(this, "Le login a �chou�", "Impossible de se logger: "+m->erreur());
    }
    else if(message->id() == 3)
    {
        QMessageBox::information(this, "Le login a r�ussi", "Login r�ussi, chargement du jeu...");
        //TODO login ok
    }
    else QMessageBox::warning(this, "Message inconnu re�u", "Un message Inconnu a �t� re�u: id = " + QString::number(message->id()));
    message->deleteLater();
}
