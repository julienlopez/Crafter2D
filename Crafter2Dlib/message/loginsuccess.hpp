#ifndef MESSAGELOGINSUCCESS_HPP
#define MESSAGELOGINSUCCESS_HPP

#include "message.hpp"

namespace Message {

class LoginSuccess : public Message
{
    Q_OBJECT
public:
    explicit LoginSuccess(quint64 idPlayer);

    quint64 idPlayer() const;

    static LoginSuccess* extract(QDataStream& in);
    virtual QDataStream& serialize(QDataStream& out) const;

    static const quint64 s_id = 3;

private:
    quint64 m_idPlayer;
};

}

#endif // MESSAGELOGINSUCCESS_HPP
