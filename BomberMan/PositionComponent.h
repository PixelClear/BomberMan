#pragma once
#include "EntityComponentSystem.h"

namespace Engine
{
    class PositionComponent : public Component
    {
    public:

        PositionComponent()
        {
            x_ = y_ = 0;
        }

        PositionComponent(int x, int y) :x_(x), y_(y)
        {

        }

        void init() override
        {

        }

        void update() override
        {
            x_++;
        }

        void render() override
        {

        }

        int x() const { return x_; }
        void x(const int x) { x_ = x; }
        int y() const { return y_; }
        void y(const int y) { y_ = y; }
        void setPos(const int x, const int y)
        {
            x_ = x;
            y_ = y;
        }

    private:
        int x_;
        int y_;
    };
}