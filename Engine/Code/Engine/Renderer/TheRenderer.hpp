#pragma once
#include "Rgba.hpp"


class Vector2;
class AABB2;
class RGBA;
class Texture;

class TheRenderer
{
public:
	TheRenderer();
	void ClearScreen(float red, float green, float blue);
	void ClearScreen(const RGBA& color);
	void SetOrtho(const Vector2& bottomLeft, const Vector2& topRight);
	void SetColor(float red, float green, float blue, float alpha);
	void SetColor(const RGBA& color);
	void SetPointSize(float size);
	void PushMatrix();
	void PopMatrix();
	void Translate(float x, float y, float z);
	void Translate(const Vector2& xy);
	void Rotate(float rotationDegrees);
	void Rotate(float rotationDegrees, float x, float y, float z);
	void Scale(float x, float y, float z);

	void DrawPoint(const Vector2& point);
	void DrawPoint(float x, float y);
	void DrawLine(const Vector2& start, const Vector2& end, float lineThickness);
	void DrawLines(Vector2* const* verts, int numVerts, float lineThickness);
	void DrawLineLoop(Vector2* const* verts, int numVerts, float lineThickness);
	void DrawAABB(const AABB2& bounds, const RGBA& color = RGBA::WHITE);
	void DrawTexturedAABB(const AABB2& bounds, const Vector2& texCoordMins, const Vector2& texCoordMaxs, const Texture& texture, const RGBA& color);
	void DrawPolygonOutline(const Vector2& center, float radius, int numSides, float radianOffset);
	void DrawPolygon(const Vector2& center, float radius, int numSides, float radianOffset);


	static TheRenderer* instance;

	static const int CIRCLE_SIDES = 50;
	static const int HEXAGON_SIDES = 6;
private:
};