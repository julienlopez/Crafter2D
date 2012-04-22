#include "requestobjectinformation.hpp"

Message::Screen::RequestObjectInformation::RequestObjectInformation(quint64 code, quint64 idPlayer): Screen(s_id), m_code(code), m_idPlayer(idPlayer)
{}

quint64 Message::Screen::RequestObjectInformation::code() const
{
    return m_code;
}

quint64 Message::Screen::RequestObjectInformation::idPlayer() const
{
    return m_idPlayer;
}

Message::Message* Message::Screen::RequestObjectInformation::extract(QDataStream& in)
{
    quint64 code, i;
    in >> code;
    in >> i;
    return new RequestObjectInformation(code,i);
}

QDataStream& Message::Screen::RequestObjectInformation::serialize(QDataStream& out) const
{
    out << id();
    out << m_code;
    out << m_idPlayer;
    return out;
}

namespace {

const bool registered = Message::Message::type_factory::instance().registerClasse(Message::Screen::RequestObjectInformation::s_id, &Message::Screen::RequestObjectInformation::extract);

}
