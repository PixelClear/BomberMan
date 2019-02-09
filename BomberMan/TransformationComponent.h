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
            scale_ = 1;
        }

		TransformationComponent(const Vector2D& position, const Vector2D& velocity, int speed) :position_(position), velocity_(velocity),speed_(speed)
        {

        }

		TransformationComponent(float x, float y)
		{
			position_.x_ = x;
			position_.y_ = y;
		}

        TransformationComponent(float x, float y, int w, int h, int s)
        {
            position_.x_ = x;
            position_.y_ = y;
            width_ = w;
            height_ = h;
            scale_ = s;
        }

        void init() override
        {
            velocity_.x_ = velocity_.y_ = 0.0f;
        }

        void update() override
        {
			position_.x_ += velocity_.x_ * speed_;
            position_.y_ += velocity_.y_ * speed_;
        }

        void render() override
        {

        }
     
        uint32_t& scale() { return scale_; }
        uint32_t scale() const { return scale_; }
        uint32_t& width() { return width_; }
        uint32_t width() const { return width_; }
        uint32_t& height() { return height_; }
        uint32_t height() const { return height_; }
		Vector2D& position() { return position_; }
		Vector2D position() const { return position_; }
        Vector2D& velocity() { return velocity_; }
        Vector2D velocity() const { return velocity_; }

	private:

		Vector2D position_; //Translation Component
        Vector2D velocity_;
        uint32_t speed_ = 3;
        uint32_t height_ = 32;
        uint32_t width_ = 32;
        uint32_t scale_ = 1;
    };
}