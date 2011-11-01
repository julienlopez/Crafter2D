#ifndef SPLAYER_HPP
#define SPLAYER_HPP

#include "dataaccessor.hpp"
#include "sworldelement.hpp"

#include <gPlayer>

class sPlayer : public gPlayer, public sWorldElement
{
public:
    sPlayer(quint64 id) throw(DataAccessor::Exception);
    virtual ~sPlayer();

    virtual void save();
};

#endif // SPLAYER_HPP
