#pragma once

namespace Engine
{
	class Vector2D
	{
	public:
		Vector2D() :x_(0.0f), y_(0.0f) {}
		Vector2D(float x, float y) :x_(x), y_(y) {}

		Vector2D(const Vector2D& rhs)
		{
			x_ = rhs.x_;
			y_ = rhs.y_;
		}

		Vector2D& operator=(const Vector2D& rhs)
		{
			x_ = rhs.x_;
			y_ = rhs.y_;
			return *this;
		}

		friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
		friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
		friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);
		friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);

		Vector2D& operator+=(const Vector2D& v1);
		Vector2D& operator*=(const Vector2D& v1);
		Vector2D& operator/=(const Vector2D& v1);
		Vector2D& operator-=(const Vector2D& v1);

        Vector2D& operator*(const int& i);

		float x_;
		float y_;

	private:

		Vector2D& add(const Vector2D& v2)
		{
			this->x_ += v2.x_;
			this->y_ += v2.y_;

			return *this;
		}

		Vector2D& subtract(const Vector2D& v2)
		{
			this->x_ -= v2.x_;
			this->y_ -= v2.y_;

			return *this;
		}

		Vector2D& multiply(const Vector2D& v2)
		{
			this->x_ *= v2.x_;
			this->y_ *= v2.y_;

			return *this;
		}

		Vector2D& divide(const Vector2D& v2)
		{
			this->x_ /= v2.x_;
			this->y_ /= v2.y_;

			return *this;
		}
	};
}
