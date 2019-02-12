#include "TileComponent.h"
#include "TransformationComponent.h"
#include "SpriteComponent.h"

Engine::TileComponent::TileComponent(SDL_Renderer* renderer, int x, int y, int w, int h, GameObjectType tileId)
{
    tilePos_.x = x;
    tilePos_.y = y;
    tilePos_.w = w;
    tilePos_.h = h;

    tileId_ = tileId;

    switch (tileId_)
    {
    case GameObjectType::BrickWall:
        path_ = "../Assets/BrickWall.png";
        break;
    case GameObjectType::GrassBlock:
        path_ = "../Assets/Grass.png";
        break;
    case GameObjectType::WaterBlock:
        path_ = "../Assets/Water.png";
        break;
    default:
        break;
    }

    renderer_ = renderer;
}

void Engine::TileComponent::init()
{
    if (path_)
    {
        entity_->addComponent<TransformationComponent>(static_cast<float>(tilePos_.x), static_cast<float>(tilePos_.y), tilePos_.w, tilePos_.h, 1);
        entity_->addComponent<SpriteComponent>(renderer_, path_);
    }
}

void Engine::TileComponent::update()
{
    spriteComponent_ = &entity_->getComponent<SpriteComponent>();
    transformation_ = &entity_->getComponent<TransformationComponent>();
}

void Engine::TileComponent::render()
{
    spriteComponent_->setDstRect(tilePos_);
}
