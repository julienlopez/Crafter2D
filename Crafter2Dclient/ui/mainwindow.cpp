#include "mainwindow.hpp"
#include "loginwidget.hpp"
#include "screenwidget.hpp"
#include "debugdock.hpp"
#include "../scene.hpp"
#include "inventorydock.hpp"

#include <Message/Login>
#include <Message/LoginFailure>
#include <Message/LoginSuccess>
#include <Message/Erreur/ErreurServeur>
#include <Message/Screen/GetPosition>

#include <QTcpSocket>
#include <QMessageBox>
#include <QLabel>
#include <QCloseEvent>

#include <stdexcept>

#include <QDebug>

UI::MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), tailleMessage(0)
{
    inventory = 0;
    showMaximized();
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
    connect(socket, SIGNAL(connected()), this, SLOT(connecte()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(deconnecte()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(erreurSocket(QAbstractSocket::SocketError)));
    connect(this, SIGNAL(messageRecu(Message::Message*)), this, SLOT(handleMessage(Message::Message*)));

    debug = new UI::DebugDock;
    addDockWidget(Qt::RightDockWidgetArea, debug, Qt::Vertical);

    setCentralWidget(new QLabel(tr("Connexion au serveur...")));
    socket->connectToHost("127.0.0.1", 50885);
}

UI::MainWindow::~MainWindow()
{}

void UI::MainWindow::closeEvent(QCloseEvent* evt)
{
    socket->close();
    evt->accept();
}

void UI::MainWindow::setUpScreen(quint64 idPlayer)
{
    centralWidget()->deleteLater();
    m_scene = new Scene(idPlayer, this);
    m_screen = new ScreenWidget(m_scene);
    connect(m_scene, SIGNAL(message(const Message::Message&)), this, SLOT(send(const Message::Message&)));
    connect(m_scene, SIGNAL(newPosition(const Position&)), debug, SLOT(setPosition(const Position&)));
    setCentralWidget(m_screen);
    send(Message::Screen::GetPosition());
    Q_ASSERT(!inventory);
    inventory = new InventoryDock(idPlayer);
    addDockWidget(Qt::RightDockWidgetArea, inventory, Qt::Vertical);
}

void UI::MainWindow::send(const Message::Message& message)
{
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);
    out << (quint16) 0;
    message.serialize(out);
    out.device()->seek(0);
    out << (quint16) (paquet.size() - sizeof(quint16));
    socket->write(paquet);
}

void UI::MainWindow::donneesRecues()
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

void UI::MainWindow::connecte()
{
    centralWidget()->deleteLater();
    LoginWidget* lw = new LoginWidget;
    connect(lw, SIGNAL(sendLogin(QString,QString)), this, SLOT(sendLogin(QString, QString)));
    setCentralWidget(lw);
}

void UI::MainWindow::deconnecte()
{

}

void UI::MainWindow::erreurSocket(QAbstractSocket::SocketError e)
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

void UI::MainWindow::sendLogin(QString login, QString mdp)
{
    send(Message::Login(login, mdp));
    QWidget* w = new QWidget;
    QWidget* l = centralWidget();
    setCentralWidget(w);
    l->deleteLater();
}

void UI::MainWindow::handleMessage(Message::Message* message)
{
    if(message->id() >= 5000 && m_scene != 0) m_scene->handleMessage(message);
    else if(message->id() == 2)
    {
        const Message::LoginFailure* m = qobject_cast<const Message::LoginFailure*>(message);
        Q_ASSERT(m != 0);
        QMessageBox::information(this, "Le login a �chou�", "Impossible de se logger: "+m->erreur());
        centralWidget()->deleteLater();
        LoginWidget* lw = new LoginWidget;
        connect(lw, SIGNAL(sendLogin(QString,QString)), this, SLOT(sendLogin(QString, QString)));
        setCentralWidget(lw);
    }
    else if(message->id() == Message::LoginSuccess::s_id)
    {
        QMessageBox::information(this, "Le login a r�ussi", "Login r�ussi, chargement du jeu...");
        const Message::LoginSuccess* l = qobject_cast<const Message::LoginSuccess*>(message);
        Q_ASSERT(l);
        setUpScreen(l->idPlayer());
    }
    else if(message->id() >= 1000 && message->id() < 3000)
    {
        qDebug() << "id: " << message->id() << " => " <<message;
        const Message::Erreur::ErreurServeur* e = qobject_cast<const Message::Erreur::ErreurServeur*>(message);
        Q_ASSERT(e != 0);
        QMessageBox::critical(this, "Erreur serveur", e->message());
        throw std::logic_error("Erreur critique");
    }
    else QMessageBox::warning(this, "Message inconnu re�u", "Un message Inconnu a �t� re�u: id = " + QString::number(message->id()));
    message->deleteLater();
}
