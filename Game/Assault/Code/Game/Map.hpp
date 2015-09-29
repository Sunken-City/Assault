#pragma once

#include "Game/Tile.hpp"
#include "Game/TileDefinition.hpp"
#include <vector>
#include <set>

class Entity;
class Camera2D;
class Tank;
class Bullet;

class Map
{
public:	
	Map(const TileCoords& size);

	~Map();
	void Update(float deltaTime);
	void Render() const;

	void CreateTileDefinitions();
	void SpawnBullet(const WorldCoords& position, float orientation, int factionNumber, float bulletSpeed, float lifespan);
	Tile* GetTileAtCoords(const TileCoords& tileCoordinates);
	Tile* GetTileAtWorldCoords(const WorldCoords& worldCoordinates);
	Tile& GetTileAtIndex(TileIndex index);
	TileCoords GetTileCoordsForTile(const Tile& tile) const;
	TileCoords GetTileCoordsFromWorldCoords(const WorldCoords& worldCoordinates) const;
	TileCoords GetTileCoordsFromIndex(int index) const;
	TileIndex GetIndexFromTileCoords(const TileCoords& tileCoordinates) const;
	bool HasLineOfSight(const WorldCoords& start, const WorldCoords& end);

	static WorldCoords GetWorldCoordsFromTileCoords(const TileCoords& tileCoords);

private:
	static const int NUM_TURRETS = 10;
	static const int NUM_TANKS = 10;

	std::vector<TileDefinition> m_definitions;
	std::vector<Tile> m_tiles;	
	TileCoords m_size;
	std::set<Entity*> m_entities;
	std::set<Bullet*> m_bullets;
	Camera2D* m_Camera;
};
