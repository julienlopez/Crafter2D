#ifndef SERVEUR_HPP
#define SERVEUR_HPP

#include <QObject>
#include <Message/Message>

#include <QAbstractSocket>

class Client;
class QTcpServer;

class Serveur : public QObject
{
    Q_OBJECT
public:
    explicit Serveur(QObject *parent = 0);

    bool start();

private:
    QList<Client*> clients;
    QTcpServer* serveur;

    void envoyerATous(const Message::Message& message);

signals:

private slots:
    void nouvelleConnexion();
    void deconnexionClient();
    void onSocketError(QAbstractSocket::SocketError);
    void onQuit();
};

#endif // SERVEUR_HPP
