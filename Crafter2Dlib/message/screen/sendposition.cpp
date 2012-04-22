#include "sendposition.hpp"

Message::Screen::SendPosition::SendPosition(const Position& position): Screen(SendPosition::s_id), m_position(position)
{}

Position Message::Screen::SendPosition::position() const
{
    return m_position;
}

Message::Message* Message::Screen::SendPosition::extract(QDataStream& in)
{
    Position p;
    in >> p;
    return new SendPosition(p);
}

QDataStream& Message::Screen::SendPosition::serialize(QDataStream& out) const
{
    out << m_id;
    out << m_position;
    return out;
}

namespace {

const bool registered = Message::Message::type_factory::instance().registerClasse(Message::Screen::SendPosition::s_id, &Message::Screen::SendPosition::extract);

}
