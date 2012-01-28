#include "majposition.hpp"
#include "../../worldelement.hpp"

Message::Screen::MajPosition::MajPosition(WorldElement* el) : Screen(s_id), m_objectCode(el->code()), m_objectId(el->id()), m_position(el->position())
{}

Message::Screen::MajPosition::MajPosition(quint64 objectCode, quint64 objectId, const Position& position) : Screen(s_id), m_objectCode(objectCode), m_objectId(objectId), m_position(position)
{}

quint64 Message::Screen::MajPosition::objectCode() const
{
    return m_objectCode;
}

quint64 Message::Screen::MajPosition::objectId() const
{
    return m_objectId;
}

Position Message::Screen::MajPosition::position() const
{
    return m_position;
}

Message::Screen::MajPosition* Message::Screen::MajPosition::extract(QDataStream& in, quint64 id)
{
    Q_ASSERT(id == MajPosition::s_id);
    quint64 obj, code;
    in >> code;
    in >> obj;
    Position p;
    in >> p;
    return new MajPosition(code, obj, p);
}

QDataStream& Message::Screen::MajPosition::serialize(QDataStream& out) const
{
    out << id();
    out << m_objectCode;
    out << m_objectId;
    out << m_position;
    return out;
}
