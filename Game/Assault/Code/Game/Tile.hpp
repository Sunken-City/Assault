#pragma once

#include "Game/GameCommon.hpp"

enum class TileType
{
	GRASS,
	STONE
};

class Tile
{
public:
	Tile();
	Tile(TileCoords position, TileType type);
	Tile(int x, int y, TileType type);
	~Tile();
	void Update(float deltaTime);
	void Render() const;
	TileCoords GetTileCoords() const;
	WorldCoords GetWorldCoordsFromTileMin() const;
	WorldCoords GetWorldCoordsFromTileCenter() const;
	TileType GetType() const;

private:
	RGBA GetColorFromType(TileType type);
	static const float TILE_SIZE;
	static const float HALF_TILE_SIZE;
	TileCoords m_tileCoords;
	TileType m_type;
	RGBA m_color;
};
