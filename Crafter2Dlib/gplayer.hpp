#ifndef GPLAYER_HPP
#define GPLAYER_HPP

#include "worldelement.hpp"
#include "position.hpp"

class gPlayer : public WorldElement
{
public:
    gPlayer(quint64 id);

    Position position() const;
    void setPosition(const Position& p);

    static const quint64 s_code = 1;

    virtual void serialize(QDataStream& out) const;
    static gPlayer* extract(QDataStream& in);

private:
    Position m_position;
};

#endif // GPLAYER_HPP
