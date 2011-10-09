#include "mainwindow.hpp"
#include "loginwidget.hpp"
#include "screenwidget.hpp"

#include <Message/Login>
#include <Message/LoginFailure>
#include <Message/LoginSuccess>
#include <Message/Screen/GetPosition>

#include <QTcpSocket>
#include <QMessageBox>
#include <QLabel>
#include <QCloseEvent>

#include <QDebug>

#include <cassert>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), tailleMessage(0)
{
    showMaximized();
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
    connect(socket, SIGNAL(connected()), this, SLOT(connecte()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(deconnecte()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(erreurSocket(QAbstractSocket::SocketError)));
    connect(this, SIGNAL(messageRecu(Message::Message*)), this, SLOT(onNewMessage(Message::Message*)));

    setCentralWidget(new QLabel(tr("Connexion au serveur...")));
    socket->connectToHost("127.0.0.1", 50885);
}

MainWindow::~MainWindow()
{}

void MainWindow::closeEvent(QCloseEvent* evt)
{
    socket->close();
    evt->accept();
}

void MainWindow::setUpScreen()
{
    centralWidget()->deleteLater();
    m_screen = new ScreenWidget;
    connect(m_screen, SIGNAL(message(Message::Message&)), this, SLOT(send(Message::Message)));
    setCentralWidget(m_screen);
    send(Message::Screen::GetPosition());
}

void MainWindow::send(const Message::Message& message)
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

    Message::Message* message = Message::Message::extract(in);
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
    static QString erreur = "Erreur réseau";
    switch(e)
    {
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::warning(this, erreur, "le serveur n'a pas pu être trouvé.");
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::warning(this, erreur, "le serveur a refusé la connexion.");
        break;
    case QAbstractSocket::RemoteHostClosedError:
        QMessageBox::warning(this, erreur, "le serveur a coupé la connexion.");
        break;
    default:
        QMessageBox::warning(this, erreur, "ERREUR : ") + socket->errorString();
    }
}

void MainWindow::sendLogin(QString login, QString mdp)
{
    send(Message::Login(login, mdp));
    QWidget* w = new QWidget;
    QWidget* l = centralWidget();
    setCentralWidget(w);
    l->deleteLater();
}

void MainWindow::onNewMessage(Message::Message* message)
{
    if(message->id() >= 5000 && m_screen != 0) m_screen->handleMessage(message);
    else if(message->id() == 2)
    {
        const Message::LoginFailure* m = qobject_cast<const Message::LoginFailure*>(message);
        assert(m != 0);
        QMessageBox::information(this, "Le login a échoué", "Impossible de se logger: "+m->erreur());
    }
    else if(message->id() == 3)
    {
        QMessageBox::information(this, "Le login a réussi", "Login réussi, chargement du jeu...");
        setUpScreen();
    }
    else QMessageBox::warning(this, "Message inconnu reçu", "Un message Inconnu a été reçu: id = " + QString::number(message->id()));
    message->deleteLater();
}
