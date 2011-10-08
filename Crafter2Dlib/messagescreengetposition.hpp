#ifndef MESSAGESCREENGETPOSITION_HPP
#define MESSAGESCREENGETPOSITION_HPP

#include "message.hpp"

class MessageScreenGetPosition : public Message
{
    Q_OBJECT
public:
    explicit MessageScreenGetPosition();

    static MessageScreenGetPosition* extract(QDataStream& in);
    virtual QDataStream& serialize(QDataStream& out) const;
};

#endif // MESSAGESCREENGETPOSITION_HPP
