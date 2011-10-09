#ifndef MESSAGEHANDLER_HPP
#define MESSAGEHANDLER_HPP

#include <QObject>

class Client;

namespace Message {
class Message;
}

class MessageHandler : public QObject
{
    Q_OBJECT
public:
    explicit MessageHandler(Client* parent);

    void traiter(const Message::Message* message) const;

private:
    Client* m_client;

signals:

public slots:

};

#endif // MESSAGEHANDLER_HPP
