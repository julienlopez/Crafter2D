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

private:
    Position m_position;
};

#endif // GPLAYER_HPP
