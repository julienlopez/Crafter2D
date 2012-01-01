#ifndef MESSAGEHANDLER_HPP
#define MESSAGEHANDLER_HPP

namespace Message {
    class Message;
}

class iMessageHandler
{
public:
    virtual void handleMessage(Message::Message* message) =0;
};

#endif // MESSAGEHANDLER_HPP
