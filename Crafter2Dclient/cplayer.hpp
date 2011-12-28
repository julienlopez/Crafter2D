#ifndef CPLAYER_HPP
#define CPLAYER_HPP

#include "cworldelement.hpp"

#include <gPlayer>

/**
  * \brief Spécialisation de la class gPlayer pour le client.
  *
  *
  */
class cPlayer : public gPlayer, public cWorldElement
{
public:
    cPlayer(quint64 id);

    void setPosition(const Position& p);
};

#endif // CPLAYER_HPP
