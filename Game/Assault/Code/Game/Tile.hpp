#pragma once

#include "Game/GameCommon.hpp"
#include "Game/TileDefinition.hpp"

class Tile
{
public:
	Tile(TileCoords position, TileDefinition* definition);
	Tile(int x, int y, TileDefinition* definition);
	~Tile();
	void Update(float deltaTime);
	void Render() const;
	TileCoords GetTileCoords() const;
	WorldCoords GetWorldCoordsFromTileMin() const;
	WorldCoords GetWorldCoordsFromTileCenter() const;
	TileType GetType() const;
	bool IsSolid() const;

private:
	static const float TILE_SIZE;
	static const float HALF_TILE_SIZE;

	TileCoords m_tileCoords;
	Texture* m_texture;
	TileDefinition* m_definition;
};
