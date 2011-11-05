#ifndef SERVEUR_HPP
#define SERVEUR_HPP

#include <QObject>
#include <Message/Message>

#include <QAbstractSocket>

class Client;
class QTcpServer;
class QTimer;
class LocalServeur;

class Serveur : public QObject
{
    Q_OBJECT
public:
    explicit Serveur(QObject *parent = 0);

    bool start();
    QString status() const;

private:
    QList<Client*> clients;
    QTcpServer* serveur;
    QTimer* m_savingTimer;
    LocalServeur* m_localServeur;

    void envoyerATous(const Message::Message& message);

signals:

private slots:
    void nouvelleConnexion();
    void deconnexionClient();
    void onSocketError(QAbstractSocket::SocketError);
    void onQuit();

public slots:
    void shutdown();
};

#endif // SERVEUR_HPP
