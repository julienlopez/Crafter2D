#include "mainwindow.hpp"
#include "loginwidget.hpp"

#include <MessageLogin>

#include <QTcpSocket>
#include <QMessageBox>
#include <QLabel>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), tailleMessage(0)
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
    connect(socket, SIGNAL(connected()), this, SLOT(connecte()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(deconnecte()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(erreurSocket(QAbstractSocket::SocketError)));

    setCentralWidget(new QLabel(tr("Connexion au serveur...")));
    socket->connectToHost("127.0.0.1", 50885);
}

MainWindow::~MainWindow()
{}

void MainWindow::send(const Message& message)
{
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    out << (quint16) 0; // On �crit 0 au d�but du paquet pour r�server la place pour �crire la taille
    out << message; // On ajoute le message � la suite
    out.device()->seek(0); // On se replace au d�but du paquet
    out << (quint16) (paquet.size() - sizeof(quint16)); // On �crase le 0 qu'on avait r�serv� par la longueur du message
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

    Message message;
    in >> message;
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
    send(MessageLogin(login, mdp));
    QWidget* w = new QWidget;
    QWidget* l = centralWidget();
    setCentralWidget(w);
    l->deleteLater();
}
