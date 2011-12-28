#ifndef GSTATICOBJECT_HPP
#define GSTATICOBJECT_HPP

#include "worldelement.hpp"

class gStaticObject : public WorldElement
{
public:
    gStaticObject(quint64 id);

    static const quint64 s_code = 3;

    virtual void serialize(QDataStream& out) const;
    static gStaticObject* extract(QDataStream& in);

    quint64 code() const;
};

#endif // GSTATICOBJECT_HPP
