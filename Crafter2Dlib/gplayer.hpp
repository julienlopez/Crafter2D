#ifndef GPLAYER_HPP
#define GPLAYER_HPP

#include "worldelement.hpp"

class gPlayer : public WorldElement
{
public:
    gPlayer(quint64 id);

    static const quint64 s_code = 1;

    virtual void serialize(QDataStream& out) const;
    static gPlayer* extract(QDataStream& in);
};

#endif // GPLAYER_HPP
