#include "Engine/Math/Vector2.hpp"
#include <math.h>

Vector2::Vector2()
{
}

Vector2::Vector2(float initialX, float initialY) 
	: x(initialX)
	, y(initialY)
{
}

Vector2::Vector2(const Vector2& other) 
	: x(other.x)
	, y(other.y)
{
}

void Vector2::SetXY(float newX, float NewY)
{
	x = newX;
	y = NewY;
}

float Vector2::CalculateMagnitude()
{
	return sqrt((x*x) + (y*y));
}

void Vector2::Normalize()
{
	float len = CalculateMagnitude();
	if (len == 0.f)return;
	x /= len;
	y /= len;
}

Vector2& Vector2::operator+=(const Vector2& rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	return *this;
}

Vector2& Vector2::operator*=(const float& scalarConstant)
{
	this->x *= scalarConstant;
	this->y *= scalarConstant;
	return *this;
}
