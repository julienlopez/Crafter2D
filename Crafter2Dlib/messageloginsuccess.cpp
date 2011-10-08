#include "messageloginsuccess.hpp"

MessageLoginSuccess::MessageLoginSuccess(): Message(3)
{}

MessageLoginSuccess* MessageLoginSuccess::extract(QDataStream& in)
{
    return new MessageLoginSuccess;
}

QDataStream& MessageLoginSuccess::serialize(QDataStream& out) const
{
    out << m_id;
    return out;
}
