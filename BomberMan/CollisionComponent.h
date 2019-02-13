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
        CollisionComponent(const std::string & t) :tag_(t) {}

        void init() override;

        void update() override;

        void render() override;

        std::string& tag() { return tag_; }
        SDL_Rect& getAABB() { return aabb_; }
        SDL_Rect getAABB() const { return aabb_; }

    private:

        SDL_Rect aabb_;
        std::string tag_;
        TransformationComponent* transform_;
        SpriteComponent* sprite_;
        
    };
}
