#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <Message/Message>

#include <QMainWindow>
#include <QAbstractSocket>

class QTcpSocket;
class ScreenWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* evt);

private:
    quint16 tailleMessage;
    QTcpSocket* socket;
    ScreenWidget* m_screen;

    void setUpScreen();

private slots:
    void send(const Message::Message& message);
    void donneesRecues();
    void connecte();
    void deconnecte();
    void erreurSocket(QAbstractSocket::SocketError);
    void sendLogin(QString, QString);
    void onNewMessage(Message::Message* message);

signals:
    void messageRecu(Message::Message*);
};

#endif // MAINWINDOW_HPP
