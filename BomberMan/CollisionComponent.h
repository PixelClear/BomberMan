#pragma once
#include "EntityComponentSystem.h"
#include "SDL.h"
#include <string>

namespace Engine
{
    class TransformationComponent;
    class SpriteComponent;
    class CollisionComponent : public Component
    {
    public:

        CollisionComponent() = default;
      

        void init() override;

        void update() override;

        void render() override;

     
    private:

        SDL_Rect aabb_;
        std::string tag_;
        TransformationComponent* transform_;
        SpriteComponent* sprite_;
        int height_;
        int width_;
    };
}
