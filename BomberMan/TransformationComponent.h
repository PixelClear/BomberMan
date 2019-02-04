#pragma once
#include "EntityComponentSystem.h"

namespace Engine
{
    class TransformationComponent : public Component
    {
    public:

		TransformationComponent()
        {
			position_.x_ = 0.0f;
			position_.y_ = 0.0f;
        }

		TransformationComponent(const Vector2D& position) :position_(position)
        {

        }

		TransformationComponent(float x, float y)
		{
			position_.x_ = x;
			position_.y_ = y;
		}

        void init() override
        {

        }

        void update() override
        {
			position_.x_++;
        }

        void render() override
        {

        }
     

		Vector2D& position() { return position_; }
		Vector2D position() const { return position_; }

	private:

		Vector2D position_; //Translation Component
    };
}