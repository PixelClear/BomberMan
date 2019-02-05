#pragma once
#include "EntityComponentSystem.h"
#include "Components.h"

namespace Engine
{
    class InputControllerComponent : public Component
    {
    public:

        InputControllerComponent() = default;

        void init() override
        {
            transformation_ = &entity_->getComponent<TransformationComponent>();
        }

        void update() override
        {
            if (GameEngine::getEvent().type == SDL_KEYDOWN)
            {
                switch (GameEngine::getEvent().key.keysym.sym)
                {
                case SDLK_w:
                    transformation_->velocity().y_ = -1.0f;
                    break;
                case SDLK_s:
                    transformation_->velocity().y_ = 1.0f;
                    break;
                case SDLK_a:
                    transformation_->velocity().x_ = -1.0f;
                    break;
                case SDLK_d:
                    transformation_->velocity().x_ = 1.0f;
                    break;
                default:
                    break;
                }
            }

            if (GameEngine::getEvent().type == SDL_KEYUP)
            {
                switch (GameEngine::getEvent().key.keysym.sym)
                {
                case SDLK_w:
                    transformation_->velocity().y_ = 0.0f;
                    break;
                case SDLK_s:
                    transformation_->velocity().y_ = 0.0f;
                    break;
                case SDLK_a:
                    transformation_->velocity().x_ = -0.0f;
                    break;
                case SDLK_d:
                    transformation_->velocity().x_ = 0.0f;
                    break;
                default:
                    break;
                }
            }
        }

        void render() override
        {

        }

    private:
        TransformationComponent* transformation_;
    };
}