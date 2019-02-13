#pragma once
#include "SDL.h"
namespace Engine
{
    class CollisionComponent;
    class Collission
    {
    public:
        static bool AABB(const SDL_Rect& a, const SDL_Rect& b);
        static bool AABB(const CollisionComponent& a, const CollisionComponent& b);
    };
}
