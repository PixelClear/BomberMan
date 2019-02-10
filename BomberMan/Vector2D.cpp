#include "Vector2D.h"

using namespace Engine;

Vector2D& Engine::operator+(Vector2D& v1, const Vector2D& v2)
{
	return v1.add(v2);
}

Vector2D& Engine::operator*(Vector2D& v1, const Vector2D& v2)
{
	return v1.multiply(v2);
}

Vector2D& Engine::operator/(Vector2D& v1, const Vector2D& v2)
{
	return v1.divide(v2);
}

Vector2D& Engine::operator-(Vector2D& v1, const Vector2D& v2)
{
	return v1.subtract(v2);
}


Vector2D& Engine::Vector2D::operator+=(const Vector2D& v1)
{
	return this->add(v1);
}

Vector2D& Engine::Vector2D::operator*=(const Vector2D& v1)
{
	return this->multiply(v1);
}

Vector2D& Engine::Vector2D::operator/=(const Vector2D& v1)
{
	return this->divide(v1);
}

Vector2D& Engine::Vector2D::operator-=(const Vector2D& v1)
{
	return this->subtract(v1);
}

Vector2D & Engine::Vector2D::operator*(const int & i)
{
    this->x_ *= i;
    this->y_ *= i;
    return *this;
}
