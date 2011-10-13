#ifndef SPLAYER_HPP
#define SPLAYER_HPP

#include "dataaccessor.hpp"

#include <gPlayer>

class sPlayer : public gPlayer
{
public:
    sPlayer(quint64 id) throw(DataAccessor::Exception);
};

#endif // SPLAYER_HPP
