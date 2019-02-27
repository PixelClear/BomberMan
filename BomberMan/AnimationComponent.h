#pragma once
#include "EntityComponentSystem.h"

namespace Engine
{
    class AnimationComponent : public Component
    {

    public:

        AnimationComponent(uint32_t frames, uint32_t speed) : frames_(frames), speed_(speed) {}
        
        void init() override;

        void update() override;

        void render() override;

        uint32_t frames() const{ return frames_; }
        uint32_t& frames() { return frames_; }
        uint32_t speed() const { return speed_; }
        uint32_t& speed() { return speed_; }

    private:
        
        uint32_t frames_ = 0;
        uint32_t speed_ = 100;
    };
}
