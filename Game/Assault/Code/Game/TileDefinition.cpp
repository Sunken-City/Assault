#include "Game/TileDefinition.hpp"
#include "Engine/Renderer/Texture.hpp"
#include "Engine/Renderer/SpriteSheet.hpp"
#include "Engine/Renderer/AABB2.hpp"

SpriteSheet* TileDefinition::m_tileSheet = nullptr;

TileDefinition::TileDefinition(TileType type, TileCoords coords, RGBA color, bool isSolid) : m_type(type), m_tileCoords(coords), m_color(color), m_isSolid(isSolid)
{
	//Sprite sheet for tiles is hard coded here
	if (m_tileSheet == nullptr)
	{
		m_tileSheet = new SpriteSheet("Data/Images/tiles.png", 4, 4);
	}
}

TileDefinition::~TileDefinition()
{

}

Texture* TileDefinition::GetTextureFromType(TileType type)
{
	if (type == TileType::GRASS)
	{
		return Texture::CreateOrGetTexture("Data/Images/Tank.png");
	}
}

bool TileDefinition::IsSolid()
{
	return m_isSolid;
}

Texture* TileDefinition::GetTexture()
{
	return m_tileSheet->GetTexture();
}

AABB2 TileDefinition::GetTextureCoordinates()
{
	return m_tileSheet->GetTexCoordsForSpriteCoords(m_tileCoords);
}

TileType TileDefinition::GetType()
{
	return m_type;
}

RGBA TileDefinition::GetColor()
{
	return m_color;
}
