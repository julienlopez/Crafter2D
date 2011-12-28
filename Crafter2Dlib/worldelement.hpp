#ifndef WORLDELEMENT_HPP
#define WORLDELEMENT_HPP

#include <QtGlobal>
#include <QDataStream>

#include "position.hpp"

class WorldElement
{
public:
    quint64 id() const;

    Position position() const;
    virtual void setPosition(const Position& p);

    virtual void serialize(QDataStream& out) const;
    static WorldElement* extract(QDataStream& in);

    virtual quint64 code() const = 0;

protected:
    WorldElement(quint64 id, const Position& position = Position());

private:
    quint64 m_id;
    Position m_position;
};

#endif // WORLDELEMENT_HPP
