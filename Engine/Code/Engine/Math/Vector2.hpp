#pragma once

class Vector2
{
public:
	Vector2();
	Vector2(float initialX, float initialY);
	Vector2(const Vector2& other);
	void SetXY(float newX, float newY);
	float CalculateMagnitude();
	void Normalize();

	Vector2& operator+=(const Vector2& rhs);
	Vector2& operator-=(const Vector2& rhs);
	Vector2& operator*=(const float& scalarConstant);

private:

public:
	float x;
	float y;
};

inline Vector2 operator+(Vector2 lhs, const Vector2& rhs)
{
	lhs += rhs;
	return lhs;
}

inline Vector2 operator-(Vector2 lhs, const Vector2& rhs)
{
	lhs -= rhs;
	return lhs;
}

inline Vector2 operator*(Vector2 lhs, const float& scalarConstant)
{
	lhs *= scalarConstant;
	return lhs;
}