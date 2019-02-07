#pragma once
#include "EntityComponentSystem.h"
#include "GameObject.h"
#include <memory>

namespace Engine
{
    class TransformationComponent;
    class SpriteComponent : public Component
    {
    public:
        SpriteComponent() = delete;
        SpriteComponent(SDL_Renderer* renderer, const char* fileName);

        ~SpriteComponent() = default;

        void init() override;

        void update() override;

        void render() override
        {
            sprite_->render(renderer_);
        }

        void setSrcRect(const SDL_Rect& src) { sprite_->setSrcRect(src); }

        void setDstRect(const SDL_Rect& dst) { sprite_->setDstRect(dst); }


    private:

        std::unique_ptr<Sprite> sprite_;
        SDL_Renderer* renderer_ = nullptr;
		TransformationComponent *positionComponent_;
    };
}
