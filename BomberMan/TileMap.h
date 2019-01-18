#pragma once
#include "SDLCallbacks.h"
#include "GameObject.h"

namespace Engine
{
    class TileMap
    {
    public:
        TileMap(uint32_t mapWidth, uint32_t mapHeight, uint32_t tileWidth = 32, uint32_t tileHeight = 32);
        ~TileMap();

        void loadMap(uint32_t** map);
        void drawMap(uint32_t** map);
    private:

        enum GamObjectType
        {
            BrickWall,
            WaterBlock,
            GrassBlock,
            TotalGameObjectTypes
        };

        uint32_t** map_;
        uint32_t mapWidth_;
        uint32_t mapHeight_;

        uint32_t tileWidth_;
        uint32_t tileHeight_;
    };
}
