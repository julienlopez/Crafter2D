#ifndef LOCALSERVEUR_HPP
#define LOCALSERVEUR_HPP

#include <Commande/Commande>

#include <QLocalSocket>

class Serveur;
class QLocalServer;

class LocalServeur : public QObject
{
    Q_OBJECT
public:
    explicit LocalServeur(Serveur* parent = 0);

private:
    quint16 tailleMessage;
    QLocalServer* m_server;
    QLocalSocket* m_socket;

    void handle(Commande::Commande* commande);

signals:

private slots:
    void newConnection();
    void onDeconnexion();
    void onError(QLocalSocket::LocalSocketError socketError);
    void onStateChanged(QLocalSocket::LocalSocketState socketState);
    void send(const Commande::Commande& commande);
    void write(const QByteArray& paquet);
    void donneesRecues();
};

#endif // LOCALSERVEUR_HPP
