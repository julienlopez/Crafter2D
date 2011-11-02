#ifndef SBUILDING_HPP
#define SBUILDING_HPP

#include "dataaccessor.hpp"
#include "sworldelement.hpp"

#include <gBuilding>

class sBuilding : public gBuilding, public sWorldElement
{
public:
    sBuilding(quint64 id) throw(DataAccessor::Exception);
    ~sBuilding();

    void save();
};

#endif // SBUILDING_HPP
