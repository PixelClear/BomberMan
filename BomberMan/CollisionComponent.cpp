#include "CollisionComponent.h"
#include "SDL.h"
#include "Components.h"

void Engine::CollisionComponent::init()
{
    if (!entity_->hasComponent< TransformationComponent>())
    {
        entity_->addComponent< TransformationComponent>();
    }

    transform_ = &entity_->getComponent<TransformationComponent>();
}

void Engine::CollisionComponent::update()
{
    aabb_.x = static_cast<int>(transform_->position().x_);
    aabb_.y = static_cast<int>(transform_->position().y_);
    aabb_.w = static_cast<int>(transform_->width() * transform_->scale());
    aabb_.h = static_cast<int>(transform_->height() * transform_->scale());
}

void Engine::CollisionComponent::render()
{

}
