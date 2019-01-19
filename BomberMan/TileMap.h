#pragma once
#include "SDLCallbacks.h"
#include "GameObject.h"

#ifdef _DEBUG
#include <iostream>
#endif

namespace Engine
{
    enum GamObjectType
    {
        BrickWall = 1,
        WaterBlock,
        GrassBlock,
        TotalGameObjectTypes
    };

    class TileMap
    {
    public:
        TileMap(SDL_Renderer* renderer, uint32_t mapWidth, uint32_t mapHeight, uint32_t tileWidth = 32, uint32_t tileHeight = 32);
        ~TileMap();

        void loadMap(uint32_t* map);
        void render();
    private:

        uint32_t** map_;
        uint32_t mapWidth_;
        uint32_t mapHeight_;

        uint32_t tileWidth_;
        uint32_t tileHeight_;

        SDL_Renderer* renderer_;
        std::unique_ptr<Sprite> grass_;
        std::unique_ptr<Sprite> brick_;
        std::unique_ptr<Sprite> water_;

        SDL_Rect src_;
        SDL_Rect dst_;

    };
}
