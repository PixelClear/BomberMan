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

}

void Engine::CollisionComponent::render()
{

}
