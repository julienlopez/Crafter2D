#ifndef CPLAYER_HPP
#define CPLAYER_HPP

#include "cworldelement.hpp"

#include <gPlayer>

/**
  * \brief Spécialisation de la class gPlayer pour le client.
  *
  *
  */
class cPlayer : public cWorldElement, public gPlayer
{
public:
    cPlayer(quint64 id, QGraphicsItem *parent);
    cPlayer(gPlayer* player);

    void setPosition(const Position& p);
    virtual Position position() const;
};

#endif // CPLAYER_HPP
