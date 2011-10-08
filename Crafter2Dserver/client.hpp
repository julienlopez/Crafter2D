#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <QObject>
#include <Message>

class QTcpSocket;
class MessageHandler;

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QTcpSocket* socket, QObject *parent = 0);

    void send(const Message& message);
    void write(const QByteArray& paquet);

    void login(const QString& login, const QString& mdp);

private:
    QTcpSocket* m_socket;
    MessageHandler* messageHandler;
    quint16 tailleMessage;

signals:
    void disconnected();

private slots:
    void donneesRecues();
};

#endif // CLIENT_HPP
