#include "sbuilding.hpp"

sBuilding::sBuilding(quint64 id): gBuilding(id)
{}

sBuilding::~sBuilding()
{

}

void sBuilding::save()
{

}

sBuilding* sBuilding::load(quint64 id) throw(DataAccessor::Exception)
{
    return 0;
}
