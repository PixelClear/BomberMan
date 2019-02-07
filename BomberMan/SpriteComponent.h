#pragma once
#include "SDL.h"
#include "EntityComponentSystem.h"
#include <memory>

namespace Engine
{
    class TransformationComponent;
    class SpriteComponent : public Component
    {
    public:
        SpriteComponent() = default;
        SpriteComponent(SDL_Renderer* renderer, const char* fileName);

        ~SpriteComponent()
        {
            SDL_DestroyTexture(texture_);
        }

        void init() override;

        void update() override;

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
