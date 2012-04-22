#include "getposition.hpp"

Message::Screen::GetPosition::GetPosition(): Screen(GetPosition::s_id)
{}

Message::Message* Message::Screen::GetPosition::extract(QDataStream& in)
{
    return new GetPosition;
}

QDataStream& Message::Screen::GetPosition::serialize(QDataStream& out) const
{
    out << m_id;
    return out;
}

namespace {

const bool registered = Message::Message::type_factory::instance().registerClasse(Message::Screen::GetPosition::s_id, &Message::Screen::GetPosition::extract);

}
