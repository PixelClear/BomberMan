#pragma once
#include "EntityComponentSystem.h"

namespace Engine
{
    class SpriteComponent;

    class AnimationComponent : public Component
    {

    public:
        void init() override
        {
            sprite_ = &entity_->getComponent<SpriteComponent>();
        }

        void update() override;

        void render() override;

    private:
        SpriteComponent* sprite_;
    };
}
