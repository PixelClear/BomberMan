#pragma once
#include "Components.h"
#include "SDL.h"
#include "GameObject.h"
#include <memory>

namespace Engine
{
    
    class SpriteComponent : public Component
    {
    public:
        SpriteComponent() = default;
        SpriteComponent(SDL_Renderer* renderer, const char* fileName)
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

        ~SpriteComponent()
        {
            SDL_DestroyTexture(texture_);
        }

        void init() override
        {
            src_.x = src_.y = 0;
            src_.w = width_; src_.h = height_;
            dst_.x = dst_.y = 0;
            dst_.w = width_; dst_.h = height_;

            positionComponent_ = &entity_->getComponent<TransformationComponent>();
        }

        void update() override
        {
            dst_.x = static_cast<int>(positionComponent_->position().x_);
            dst_.y = static_cast<int>(positionComponent_->position().y_);

        }

        void render() override
        {
            SDL_RenderCopy(renderer_, texture_, &src_, &dst_);
        }

        void setSrcRect(const SDL_Rect& src) { src_ = src; }

        void setDstRect(const SDL_Rect& dst) { dst_ = dst; }


    private:
        SDL_Rect src_;
        SDL_Rect dst_;
        int width_;
        int height_;
        SDL_Texture* texture_ = nullptr;
        SDL_Renderer* renderer_ = nullptr;
		TransformationComponent *positionComponent_;
    };
}
