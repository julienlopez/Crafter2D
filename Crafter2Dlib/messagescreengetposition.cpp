#include "messagescreengetposition.hpp"

MessageScreenGetPosition::MessageScreenGetPosition() :
    Message(5001)
{
}

MessageScreenGetPosition* MessageScreenGetPosition::extract(QDataStream& in)
{
    return new MessageScreenGetPosition;
}

QDataStream& MessageScreenGetPosition::serialize(QDataStream& out) const
{
    out << m_id;
    return out;
}
