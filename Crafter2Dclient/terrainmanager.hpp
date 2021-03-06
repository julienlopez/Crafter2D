#ifndef TERRAINMANAGER_HPP
#define TERRAINMANAGER_HPP

#include <Utils/Singleton>

#include <QtGlobal>

class TerrainManager : public Utils::Singleton<TerrainManager>
{
    friend class Utils::Singleton<TerrainManager>;

public:
    typedef quint8 Terrain;

    static Terrain get(int x, int y);

    static const Terrain sand = 0;
    static const Terrain grass = 1;
    static const Terrain water = 2;

private:
    TerrainManager();

    Terrain s_get(int x, int y) const;
};

#endif // TERRAINMANAGER_HPP
