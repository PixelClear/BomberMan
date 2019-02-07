#pragma once
#include "EntityComponentSystem.h"

namespace Engine
{
    class TransformationComponent;

    class InputControllerComponent : public Component
    {
    public:

        InputControllerComponent() = default;

        void init() override;

        void update() override;

        void render() override
        {

        }

    private:
        TransformationComponent* transformation_;
    };
}