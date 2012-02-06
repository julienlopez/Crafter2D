#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <iMessageHandler>

#include <QMainWindow>
#include <QAbstractSocket>

class QTcpSocket;
class Scene;

namespace UI {

class DebugDock;
class ScreenWidget;
class InventoryDock;

class MainWindow : public QMainWindow, public iMessageHandler
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
    Scene* m_scene;
    UI::ScreenWidget* m_screen;
    UI::DebugDock* debug;
    UI::InventoryDock* inventory;

    void setUpScreen(quint64 idPlayer);

private slots:
    void send(const Message::Message& message);
    void donneesRecues();
    void connecte();
    void deconnecte();
    void erreurSocket(QAbstractSocket::SocketError);
    void sendLogin(QString, QString);
    void handleMessage(Message::Message* message);

signals:
    void messageRecu(Message::Message*);
};

}

#endif // MAINWINDOW_HPP
