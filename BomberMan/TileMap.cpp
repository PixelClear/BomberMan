#include "TileMap.h"

Engine::TileMap::TileMap(uint32_t mapWidth, uint32_t mapHeight, uint32_t tileWidth = 32, uint32_t tileHeight = 32) :
    mapWidth_(mapWidth), mapHeight_(mapHeight), tileWidth_(tileWidth), tileHeight_(tileHeight)
{
    map_ = new uint32_t*[mapWidth_];
    for (uint32_t i = 0; i < mapWidth_; i++)
    {
        map_[i] = new uint32_t[mapHeight_];
    }

    for (uint32_t i = 0; i < mapWidth_; i++)
    {
        for (uint32_t j = 0; j < mapHeight_; j++)
        {
            map_[i][j] = 0;
        }
    }
}

Engine::TileMap::~TileMap()
{
    for (uint32_t i = 0; i < mapWidth_; i++)
    {
        delete[] map_[i];
    }

    delete [] map_;
}

void Engine::TileMap::loadMap(uint32_t** map)
{
    for (uint32_t i = 0; i < mapWidth_; i++)
    {
        for (uint32_t j = 0; j < mapHeight_; j++)
        {
            map_[i][j] = map[i][j];
        }
    }
}

void Engine::TileMap::drawMap(uint32_t** map)
{
    for (uint32_t i = 0; i < mapWidth_; i++)
    {
        for (uint32_t j = 0; j < mapHeight_; j++)
        {
            const uint32_t gameObjectType = map_[i][j];

            switch (gameObjectType)
            {
            case GamObjectType::BrickWall :
                break;
            case GamObjectType::GrassBlock:
                break;
            case GamObjectType::WaterBlock:
                break;
            }
        }
    }
}

