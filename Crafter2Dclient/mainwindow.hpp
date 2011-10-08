#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <Message>

#include <QMainWindow>
#include <QAbstractSocket>

class QTcpSocket;
class Screen;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    quint16 tailleMessage;
    QTcpSocket* socket;
    Screen* m_screen;

    void setUpScreen();

private slots:
    void send(const Message& message);
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
