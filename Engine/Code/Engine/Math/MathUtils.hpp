#pragma once

class Vector2;

class MathUtils
{
public:
	static float Lerp(float fraction, float initialValue, float endValue);
	static Vector2 Lerp(float fraction, const Vector2& initialValue, const Vector2& endValue);
	static float DegreesToRadians(float degrees);
	static float RadiansToDegrees(float radians);
	static float CalcDistanceBetweenPoints(const Vector2& pos1, const Vector2& pos2);
	static float CalcDistSquaredBetweenPoints(const Vector2& pos1, const Vector2& pos2);
	static float RangeMap(float inValue, float min1, float max1, float min2, float max2);
	static float Clamp(float inputValue);
	static float Clamp(float inputValue, float min, float max);
	static int Clamp(int inputValue, int min, int max);
	static bool DoDiscsOverlap(const Vector2& center1, float radius1, const Vector2& center2, float radius2);
	static bool IsPointInDisk(const Vector2& point, const Vector2&  center, float radius);
	static float CalcShortestAngularDisplacement(float fromDegrees, float toDegrees);
	static int GetRandom(int minimum, int maximum);
	static float GetRandom();
	static float GetRandom(float minimum, float maximum);
	static float GetRandomFromZeroTo(float maximum);
	static float Dot(const Vector2 & a, const Vector2 & b);

	static const float pi;
	static const float twoPi;
};