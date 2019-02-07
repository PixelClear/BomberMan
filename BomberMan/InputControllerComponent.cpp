#include "InputControllerComponent.h"
#include "SDL.h"
#include "Game.h"
#include "Components.h"

void Engine::InputControllerComponent::init()
{
    transformation_ = &entity_->getComponent<TransformationComponent>();
}

void Engine::InputControllerComponent::update()
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
