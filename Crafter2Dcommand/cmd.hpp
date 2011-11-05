#ifndef CMD_HPP
#define CMD_HPP

#include <Commande/Commande>

#include <QObject>
#include <QLocalSocket>

class Cmd : public QObject
{
    Q_OBJECT
public:
    explicit Cmd(QObject *parent = 0);

    void start();

private:
    bool boucle;
    quint16 tailleMessage;
    QTextStream out;
    QTextStream in;
    QLocalSocket* m_socket;

    void handle(Commande::Commande* commande);

signals:
    void quit();

private slots:
    void process(QString str);
    void onConnexion();
    void onDeconnexion();
    void onError(QLocalSocket::LocalSocketError socketError);
    void onStateChanged(QLocalSocket::LocalSocketState socketState);
    void send(const Commande::Commande& commande);
    void write(const QByteArray& paquet);
    void donneesRecues();
};

#endif // CMD_HPP
