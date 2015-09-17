#include "Engine/Renderer/SpriteSheet.hpp"
#include "Engine/Renderer/AABB2.hpp"

SpriteSheet::SpriteSheet(const Vector2Int& tileSize, const Texture& texture) : m_texture(texture), m_tileSize(tileSize)
{

}


AABB2 SpriteSheet::GetTexCoordsForSpriteCoords(const Vector2Int& spriteCoords)
{
	AABB2 texCoords;
	texCoords.mins.x = m_texCoordsPerTile.x * (float)spriteCoords.x;
	texCoords.mins.y = m_texCoordsPerTile.y * (float)spriteCoords.y;

	texCoords.maxs = texCoords.mins + m_texCoordsPerTile;
	return texCoords;
}
