#include "collission.h"
#include "CollisionComponent.h"

bool Engine::Collission::AABB(const SDL_Rect & a, const SDL_Rect & b)
{
    if ((a.x == 0 && a.y == 0 && a.w == 0 && a.h == 0) || (b.x == 0 && b.y == 0 && b.w == 0 && b.h == 0))
        return false;

    if (a.x + a.w >= b.x &&
        b.x + b.w >= a.x &&
        a.y + a.h >= b.y &&
        b.y + b.h >= a.y)
        return true;

    return false;
}

bool Engine::Collission::AABB(const CollisionComponent & a, const CollisionComponent & b)
{
    return Collission::AABB(a.getAABB(), b.getAABB());
}
