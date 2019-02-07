#include "SpriteComponent.h"
#include "SDL_image.h"
#include "Components.h"

Engine::SpriteComponent::SpriteComponent(SDL_Renderer * renderer, const char * fileName)
{
    SDL_Surface* tmpSurf = IMG_Load(fileName);
    if (!tmpSurf)
    {
        throw std::runtime_error("Failed to create surface!!");
    }

    texture_ = SDL_CreateTextureFromSurface(renderer, tmpSurf);
    if (!texture_)
    {
        SDL_FreeSurface(tmpSurf);
        throw std::runtime_error("Failed to create texture!!");
    }

    width_ = tmpSurf->w;
    height_ = tmpSurf->h;
    SDL_FreeSurface(tmpSurf);
    renderer_ = renderer;
}

void Engine::SpriteComponent::init()
{
    src_.x = src_.y = 0;
    src_.w = width_; src_.h = height_;
    dst_.x = dst_.y = 0;
    dst_.w = width_; dst_.h = height_;

    positionComponent_ = &entity_->getComponent<TransformationComponent>();
}

void Engine::SpriteComponent::update()
{
    dst_.x = static_cast<int>(positionComponent_->position().x_);
    dst_.y = static_cast<int>(positionComponent_->position().y_);
}
