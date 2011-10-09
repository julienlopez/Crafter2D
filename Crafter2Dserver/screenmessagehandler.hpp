#ifndef SCREENMESSAGEHANDLER_HPP
#define SCREENMESSAGEHANDLER_HPP

#include <QObject>

class Client;

namespace Message {
    class Message;
}

class ScreenMessageHandler : public QObject
{
    Q_OBJECT
public:
    ScreenMessageHandler(Client *parent);

    void traiter(const Message::Message* message) const;
    void sendPosition() const;

private:
    Client* m_client;

signals:

public slots:

};

#endif // SCREENMESSAGEHANDLER_HPP
