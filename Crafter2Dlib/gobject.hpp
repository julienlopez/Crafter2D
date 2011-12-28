#ifndef GOBJECT_HPP
#define GOBJECT_HPP

#include "worldelement.hpp"

class gObject : public WorldElement
{
public:
    gObject(quint64 id);

    static const quint64 s_code = 4;

    virtual void serialize(QDataStream& out) const;
    static gObject* extract(QDataStream& in);

    quint64 code() const;
};

#endif // GOBJECT_HPP
