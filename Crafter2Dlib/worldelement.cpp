#include "worldelement.hpp"

WorldElement::WorldElement(quint64 id): m_id(id)
{}

quint64 WorldElement::id() const
{
    return m_id;
}

void WorldElement::serialize(QDataStream& out) const
{

}

WorldElement* WorldElement::extract(QDataStream& in)
{

}
