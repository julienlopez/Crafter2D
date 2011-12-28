#ifndef GBUILDING_HPP
#define GBUILDING_HPP

#include "worldelement.hpp"

class gBuilding : public WorldElement
{
public:
    gBuilding(quint64 id);

    static const quint64 s_code = 2;

    virtual void serialize(QDataStream& out) const;
    static gBuilding* extract(QDataStream& in);

    quint64 code() const;
};

#endif // GBUILDING_HPP
