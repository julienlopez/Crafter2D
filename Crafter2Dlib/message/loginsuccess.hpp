#ifndef MESSAGELOGINSUCCESS_HPP
#define MESSAGELOGINSUCCESS_HPP

#include "message.hpp"

namespace Message {

class LoginSuccess : public Message
{
    Q_OBJECT
public:
    explicit LoginSuccess();

    static LoginSuccess* extract(QDataStream& in);
    virtual QDataStream& serialize(QDataStream& out) const;

    static const quint64 s_id = 3;
};

}

#endif // MESSAGELOGINSUCCESS_HPP
