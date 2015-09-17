#pragma once

#include "Game/Tile.hpp"
#include <vector>
#include <set>

class Entity;
class Camera2D;

class Map
{
public:	
	Map(const TileCoords& size);
	~Map();
	void Update(float deltaTime);
	void Render() const;

	Tile* GetTileAtCoords(const TileCoords& tileCoordinates);
	Tile& GetTileAtIndex(TileIndex index);
	Tile* GetTileAtWorldCoords(const WorldCoords& worldCoordinates);

	TileCoords GetTileCoordsForTile(const Tile& tile) const;
	TileCoords GetTileCoordsFromWorldCoords(const WorldCoords& worldCoordinates) const;
	TileCoords GetTileCoordsFromIndex(int index) const;

	static WorldCoords GetWorldCoordsFromTileCoords(const TileCoords& tileCoords);

	TileIndex GetIndexFromTileCoords(const TileCoords& tileCoordinates) const;

private:
	std::vector<Tile> m_tiles;	
	TileCoords m_size;
	std::set<Entity*> m_entities;
	Camera2D* m_Camera;
};
