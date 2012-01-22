#include "terrainmanager.hpp"

TerrainManager::Terrain TerrainManager::get(int x, int y)
{
    return instance().s_get(x,y);
}

TerrainManager::TerrainManager()
{
}

TerrainManager::Terrain TerrainManager::s_get(int x, int y) const
{
    if(x < 5 && x > -5 && y < 5 && y > -5) return grass;
    return sand;
}
