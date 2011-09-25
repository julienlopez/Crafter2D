#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <QObject>
#include <Message>

class QTcpSocket;

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QTcpSocket* socket, QObject *parent = 0);

    void send(const Message& message);
    void write(const QByteArray& paquet);

private:
    QTcpSocket* m_socket;
    quint16 tailleMessage;

signals:
    void disconnected();

private slots:
    void donneesRecues();
};

#endif // CLIENT_HPP
