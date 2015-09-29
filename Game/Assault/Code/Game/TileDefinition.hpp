#pragma once
#include "Game/GameCommon.hpp"

class SpriteSheet;

enum class TileType
{
	GRASS,
	DIRT,
	STONE
};

class TileDefinition
{
public:
	TileDefinition(TileType type, TileCoords coords, RGBA color, bool isSolid);
	~TileDefinition();
	TileType GetType();
	RGBA GetColor();
	Texture* GetTexture();
	AABB2 GetTextureCoordinates();
	bool IsSolid();

private:
	static Texture* GetTextureFromType(TileType type);
	static SpriteSheet* m_tileSheet;

	TileCoords m_tileCoords;
	TileType m_type;
	RGBA m_color;
	bool m_isSolid;
};