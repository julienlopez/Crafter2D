#include "setposition.hpp"

Message::Screen::SetPosition::SetPosition(const Position& position): Screen(SetPosition::s_id), m_position(position)
{}

Position Message::Screen::SetPosition::position() const
{
    return m_position;
}

Message::Message* Message::Screen::SetPosition::extract(QDataStream& in)
{
    Position p;
    in >> p;
    return new SetPosition(p);
}

QDataStream& Message::Screen::SetPosition::serialize(QDataStream& out) const
{
    out << m_id;
    out << m_position;
    return out;
}

namespace {

const bool registered = Message::Message::type_factory::instance().registerClasse(Message::Screen::SetPosition::s_id, &Message::Screen::SetPosition::extract);

}
