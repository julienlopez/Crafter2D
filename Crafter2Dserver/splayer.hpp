#ifndef SPLAYER_HPP
#define SPLAYER_HPP

#include "dataaccessor.hpp"
#include "sworldelement.hpp"

#include <gPlayer>

class sPlayer : public gPlayer, public sWorldElement
{
public:
    virtual ~sPlayer();

    virtual void save();

    static sPlayer* load(quint64 id) throw(DataAccessor::Exception);

private:
    sPlayer(quint64 id);
};

#endif // SPLAYER_HPP
