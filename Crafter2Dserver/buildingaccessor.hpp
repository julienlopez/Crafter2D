#ifndef BUILDINGACCESSOR_HPP
#define BUILDINGACCESSOR_HPP

#include "faccessor.hpp"

#include <gBuilding>

class BuildingAccessor : public fAccessor<gBuilding, gBuilding>
{
public:
    BuildingAccessor();
};

#endif // BUILDINGACCESSOR_HPP
