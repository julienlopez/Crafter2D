#ifndef PLAYERACCESSOR_HPP
#define PLAYERACCESSOR_HPP

#include "faccessor.hpp"
#include "splayer.hpp"

class PlayerAccessor : public fAccessor<gPlayer, sPlayer>
{
public:
    PlayerAccessor();
};

#endif // PLAYERACCESSOR_HPP
