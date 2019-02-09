#pragma once
#include "SDL.h"
namespace Engine
{
    class Collission
    {
    public:
        static bool AABB(const SDL_Rect& a, const SDL_Rect& b);
    };
}
