#ifndef BUILDINGACCESSOR_HPP
#define BUILDINGACCESSOR_HPP

#include "faccessor.hpp"
#include "sbuilding.hpp"

class BuildingAccessor : public fAccessor<gBuilding, sBuilding>
{
public:
    BuildingAccessor();
};

#endif // BUILDINGACCESSOR_HPP
