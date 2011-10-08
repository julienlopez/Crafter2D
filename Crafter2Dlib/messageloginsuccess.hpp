#ifndef MESSAGELOGINSUCCESS_HPP
#define MESSAGELOGINSUCCESS_HPP

#include "message.hpp"

class MessageLoginSuccess : public Message
{
    Q_OBJECT
public:
    explicit MessageLoginSuccess();

    static MessageLoginSuccess* extract(QDataStream& in);
    virtual QDataStream& serialize(QDataStream& out) const;

};

#endif // MESSAGELOGINSUCCESS_HPP
