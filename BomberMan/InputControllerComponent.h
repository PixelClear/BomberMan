#pragma once
#include "EntityComponentSystem.h"
#include "Components.h"
#include "Game.h"

using namespace Engine;
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
            if (Engine::GameEngine::event_.type == SDL_KEYDOWN)
            {
                switch (Engine::GameEngine::event_.key.keysym.sym)
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

            if (Engine::GameEngine::event_.type == SDL_KEYUP)
            {
                switch (Engine::GameEngine::event_.key.keysym.sym)
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