#include "loginsuccess.hpp"

Message::LoginSuccess::LoginSuccess(): Message(LoginSuccess::s_id)
{}

Message::LoginSuccess* Message::LoginSuccess::extract(QDataStream& in)
{
    return new LoginSuccess;
}

QDataStream& Message::LoginSuccess::serialize(QDataStream& out) const
{
    out << m_id;
    return out;
}
