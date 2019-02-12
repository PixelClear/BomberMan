#pragma once
#include "EntityComponentSystem.h"
#include "SDL.h"

namespace Engine
{
    class TransformationComponent;
    class SpriteComponent;

    enum GameObjectType
    {
        BrickWall = 1,
        WaterBlock,
        GrassBlock,
        TotalGameObjectTypes
    };

    class TileComponent : public Component
    {
    public:
        TileComponent() = default;
        TileComponent(SDL_Renderer* renderer, int x, int y, int w, int h, GameObjectType tileId);

        void init() override;
        void update() override;
        void render() override;

    private:

        SpriteComponent* spriteComponent_;
        TransformationComponent* transformation_;
        const char* path_;
        GameObjectType tileId_;
        SDL_Rect tilePos_;
        SDL_Renderer* renderer_;
    };
}
