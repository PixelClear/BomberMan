#pragma once
#include "EntityComponentSystem.h"
#include "GameObject.h"
#include <memory>

namespace Engine
{
    class TransformationComponent;
    class AnimationComponent;

    class SpriteComponent : public Component
    {
    public:
        SpriteComponent() = delete;
        SpriteComponent(SDL_Renderer* renderer, const char* fileName);
        SpriteComponent(SDL_Renderer * renderer, const char * fileName, uint32_t frames, uint32_t speed);
        ~SpriteComponent() = default;

        void init() override;

        void update() override;

        void render() override
        {
            sprite_->render(renderer_);
        }

        void setSrcRect(const SDL_Rect& src) { sprite_->setSrcRect(src); }
        void setDstRect(const SDL_Rect& dst) { sprite_->setDstRect(dst); }
        SDL_Rect& getSrcRect() { return sprite_->getSrcRect(); }
        SDL_Rect& getDstRect() { return sprite_->getDstRect(); }
        void setAnimated(const bool animated) { sprite_->animated() = animated; }
        bool getAnimated() const { return sprite_->animated(); }

    private:
        
        std::unique_ptr<Sprite> sprite_;
        SDL_Renderer* renderer_ = nullptr;
		TransformationComponent *positionComponent_;
        AnimationComponent *animationComponent_;
        uint32_t frames_;
        uint32_t speed_;
    };
}
