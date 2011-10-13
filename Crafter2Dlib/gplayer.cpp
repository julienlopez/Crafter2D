#include "gplayer.hpp"

gPlayer::gPlayer(quint64 id): WorldElement(id)
{}

Position gPlayer::position() const
{
    return m_position;
}

void gPlayer::setPosition(const Position& p)
{
    m_position = p;
}
