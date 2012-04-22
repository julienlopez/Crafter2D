#include "screen.hpp"
#include "getposition.hpp"
#include "setposition.hpp"
#include "sendposition.hpp"
#include "majposition.hpp"
#include "requestobjectinformation.hpp"
#include "objectinformation.hpp"

Message::Screen::Screen::Screen(quint64 id): Message(id)
{}

Message::Message* Message::Screen::Screen::extract(QDataStream& in)
{
    return new Screen(s_id);
}

QDataStream& Message::Screen::Screen::serialize(QDataStream& out) const
{
    out << m_id;
    return out;
}

namespace {

const bool registered = Message::Message::type_factory::instance().registerClasse(Message::Screen::Screen::s_id, &Message::Screen::Screen::extract);

}
