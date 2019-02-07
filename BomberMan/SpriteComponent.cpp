#include "SpriteComponent.h"
#include "SDL_image.h"
#include "Components.h"

Engine::SpriteComponent::SpriteComponent(SDL_Renderer * renderer, const char * fileName)
{
    renderer_ = renderer;
    sprite_ = std::make_unique<Sprite>(renderer_, fileName);
    
    if (!sprite_)
    {
        throw std::runtime_error("Failed to create sprite!!");
    }
}

void Engine::SpriteComponent::init()
{
    SDL_Rect src;
    SDL_Rect dst;
    const int w = static_cast<int>(sprite_->getWidth());
    const int h = static_cast<int>(sprite_->getHeight());
    src.x = src.y = 0;
    src.w = w; src.h = h;
    dst.x = dst.y = 0;
    dst.w = w; dst.h = h;

    sprite_->setSrcRect(src);
    sprite_->setDstRect(dst);

    positionComponent_ = &entity_->getComponent<TransformationComponent>();
}

void Engine::SpriteComponent::update()
{
    sprite_->getDstRect().x = static_cast<int>(positionComponent_->position().x_);
    sprite_->getDstRect().y = static_cast<int>(positionComponent_->position().y_);
}
