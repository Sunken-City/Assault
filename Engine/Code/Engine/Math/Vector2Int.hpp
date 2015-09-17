#pragma once

class Vector2Int
{
public:
	Vector2Int();
	Vector2Int(int initialX, int initialY);
	Vector2Int(const Vector2Int& other);
	void SetXY(int newX, int newY);

	Vector2Int& operator+=(const Vector2Int& rhs);
	Vector2Int& operator-=(const Vector2Int& rhs);
	Vector2Int& operator*=(const int& scalarConstant);
private:

public:
	int x;
	int y;
};

inline Vector2Int operator+(Vector2Int lhs, const Vector2Int& rhs)
{
	lhs += rhs;
	return lhs;
}

inline Vector2Int operator-(Vector2Int lhs, const Vector2Int& rhs)
{
	lhs -= rhs;
	return lhs;
}

inline Vector2Int operator*(Vector2Int lhs, const int& scalarConstant)
{
	lhs *= scalarConstant;
	return lhs;
}