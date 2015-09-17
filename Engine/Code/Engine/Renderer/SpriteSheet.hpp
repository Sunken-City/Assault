#pragma once

#include "Engine/Math/Vector2.hpp"
#include "Engine/Math/Vector2Int.hpp"
#include "Engine/Renderer/Texture.hpp"

class AABB2;

class SpriteSheet
{
public:
	SpriteSheet(const Vector2Int& tileSize, const Texture& texture);
	AABB2 GetTexCoordsForSpriteCoords(const Vector2Int& spriteCoords);

private:
	Vector2 m_texCoordsPerTile; //One step of tile in tile coords
	Vector2Int m_tileSize;

	const Texture& m_texture;

	SpriteSheet& operator=(const SpriteSheet&);
};
