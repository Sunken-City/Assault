#include "Engine/Math/MathUtils.hpp"
#include "Engine/Math/Vector2.hpp"
#include <math.h>

float MathUtils::Lerp(float fraction, float initialValue, float endValue)
{
	return initialValue + fraction * (endValue - initialValue);
}

Vector2 MathUtils::Lerp(float fraction, const Vector2& initialValue, const Vector2& endValue)
{
	return initialValue + ((endValue - initialValue) * fraction);
}

float MathUtils::DegreesToRadians(float degrees)
{
	return degrees * (pi / 180.0f);
}

float MathUtils::RadiansToDegrees(float radians)
{
	return radians * (180.0f / pi);
}

float MathUtils::CalcDistanceBetweenPoints(const Vector2& pos1, const Vector2& pos2)
{
	float xDist = pos2.x - pos1.x;
	float yDist = pos2.y - pos1.y;
	return sqrt(xDist * xDist + yDist * yDist);
}


float MathUtils::CalcDistSquaredBetweenPoints(const Vector2& pos1, const Vector2& pos2)
{
	float xDist = pos2.x - pos1.x;
	float yDist = pos2.y - pos1.y;
	return xDist * xDist + yDist * yDist;
}

float MathUtils::RangeMap(float inValue, float min1, float max1, float min2, float max2)
{
	//@TODO: Make sure max1 - min1 != 0
	return min2 + ((max2 - min2) * ((inValue - min1) / (max1 - min1)));
}

float MathUtils::Clamp(float inputValue, float min, float max)
{
	if (inputValue < min)
	{
		return min;
	}
	else if (inputValue > max)
	{
		return max;
	}
	else
	{
		return inputValue;
	}
}

float MathUtils::Clamp(float inputValue)
{
	return Clamp(inputValue, 0.0f, 1.0f);
}

bool MathUtils::DoDiscsOverlap(const Vector2& center1, float radius1, const Vector2& center2, float radius2)
{
	float distSquared = CalcDistSquaredBetweenPoints(center1, center2);
	float radii = radius1 + radius2;
	return distSquared < (radii * radii);
}

bool MathUtils::IsPointInDisk(const Vector2& point, const Vector2& center, float radius)
{
	//A point is a disk with radius 0
	return DoDiscsOverlap(point, 0.f, center, radius);
}

const float MathUtils::pi = 3.14159265358f;

const float MathUtils::twoPi = 3.14159265358f * 2.0f;
