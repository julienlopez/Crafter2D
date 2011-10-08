#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <Message>

#include <QMainWindow>
#include <QAbstractSocket>

class QTcpSocket;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    quint16 tailleMessage;
    QTcpSocket* socket;

    void send(const Message& message);

private slots:
    void donneesRecues();
    void connecte();
    void deconnecte();
    void erreurSocket(QAbstractSocket::SocketError);
    void sendLogin(QString, QString);
    void onNewMessage(Message* message);

signals:
    void messageRecu(Message*);
};

#endif // MAINWINDOW_HPP
