#include "cplayer.hpp"

cPlayer::cPlayer(quint64 id): gPlayer(id), cWorldElement()
{
}

void cPlayer::setPosition(const Position& p) {
    gPlayer::setPosition(p);
    cWorldElement::setPosition(p);
}
