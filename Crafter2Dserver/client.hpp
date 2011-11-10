#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "clientinfo.hpp"

#include <QObject>
#include <Position>
#include <Message/Message>

class QTcpSocket;
class MessageHandler;

class Client : public QObject, public ClientInfo
{
    Q_OBJECT
public:
    Client(QTcpSocket* socket, QObject *parent = 0);
    ~Client();

    void send(const Message::Message& message);
    void write(const QByteArray& paquet);

    void login(const QString& login, const QString& mdp);

private:
    QTcpSocket* m_socket;
    MessageHandler* messageHandler;
    quint16 tailleMessage;

signals:
    void disconnected();
    void positionUpdated(quint64 id, const Position& position);

private slots:
    void donneesRecues();

public slots:
    void updatePosition(const Position& position);
};

#endif // CLIENT_HPP
