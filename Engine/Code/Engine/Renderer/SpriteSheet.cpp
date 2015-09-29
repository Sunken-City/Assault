#include "Engine/Renderer/SpriteSheet.hpp"
#include "Engine/Renderer/AABB2.hpp"
#include "Engine/Renderer/Texture.hpp"


SpriteSheet::SpriteSheet(const std::string& imageFilePath, int tilesWide, int tilesHigh) 
: m_spriteLayout(Vector2Int(tilesWide, tilesHigh))
, m_spriteSheetTexture(Texture::CreateOrGetTexture(imageFilePath))
, m_texCoordsPerTile(Vector2(1.0f / tilesWide, 1.0f / tilesHigh))
{

}

AABB2 SpriteSheet::GetTexCoordsForSpriteCoords(const Vector2Int& spriteCoords) const
{
	AABB2 texCoords;
	texCoords.mins.x = m_texCoordsPerTile.x * (float)spriteCoords.x;
	texCoords.mins.y = m_texCoordsPerTile.y * (float)spriteCoords.y;

	texCoords.maxs = texCoords.mins + m_texCoordsPerTile;
	return texCoords;
}

AABB2 SpriteSheet::GetTexCoordsForSpriteIndex(int spriteIndex) const
{
	AABB2 texCoords;
	int tileY = spriteIndex / m_spriteLayout.x;
	int tileX = spriteIndex % m_spriteLayout.x;
	texCoords.mins.x = m_texCoordsPerTile.x * (float)tileX;
	texCoords.mins.y = m_texCoordsPerTile.y * (float)tileY;

	texCoords.maxs = texCoords.mins + m_texCoordsPerTile;
	return texCoords;
}

int SpriteSheet::GetNumSprites() const
{
	return m_spriteLayout.x * m_spriteLayout.y;
}

Texture* SpriteSheet::GetTexture()
{
	return m_spriteSheetTexture;
}
