#ifndef SBUILDING_HPP
#define SBUILDING_HPP

#include "dataaccessor.hpp"
#include "sworldelement.hpp"

#include <gBuilding>

class sBuilding : public gBuilding, public sWorldElement
{
public:
    ~sBuilding();

    void save();

    static sBuilding* load(quint64 id) throw(DataAccessor::Exception);

protected:
    sBuilding(quint64 id);
};

#endif // SBUILDING_HPP
