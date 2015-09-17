#include "Game/Map.hpp"
#include "Game/GameCommon.hpp"
#include "Game/TheGame.hpp"
#include "Game/Tank.hpp"
#include "Game/Camera2D.hpp"

Map::Map(const TileCoords& size) : m_size(size)
{
	TileCoords tankSpawnLocation;
	for (int y = 0; y < m_size.y; y++)
	{
		for (int x = 0; x < m_size.x; x++)
		{
			TileType type = TileType::GRASS;
			//If the tile is on the border, make it stone.
			if (y == 0 || x == 0 || y == m_size.y - 1 || x == m_size.x - 1)
			{
				type = TileType::STONE;
			}
			//Set a few tiles to stone inside
			else if (TheGame::instance->GetRandom(0, 10) == 1)
			{
				type = TileType::STONE;
			}
			//Set the last grass tile to be our spawn location.
			if (type == TileType::GRASS)
			{
				tankSpawnLocation = TileCoords(x, y);
			}
			m_tiles.push_back(Tile(x, y, type));
		}
	}
	Tank* tank = new Tank(Map::GetWorldCoordsFromTileCoords(tankSpawnLocation), this);

	m_entities.insert(tank);
	m_Camera = new Camera2D(tank);
}

Map::~Map()
{
}

void Map::Update(float deltaTime)
{
	for (std::set<Entity*>::iterator iter = m_entities.begin(); iter != m_entities.end(); ++iter)
	{
		Entity* gameObject = *iter;
		gameObject->Update(deltaTime);
	}
}

void Map::Render() const
{
	for (int y = 0; y < m_size.y; y++)
	{
		for (int x = 0; x < m_size.x; x++)
		{
			TileIndex tileIndex = GetIndexFromTileCoords(TileCoords(x, y));
			m_tiles[ tileIndex ].Render();
		}
	}

	for (std::set<Entity*>::iterator iter = m_entities.begin(); iter != m_entities.end(); ++iter)
	{
		Entity* gameObject = *iter;
		gameObject->Render();
	}

	m_Camera->Render();
}

TileCoords Map::GetTileCoordsForTile(const Tile& tile) const
{
	return tile.GetTileCoords();
}

Tile* Map::GetTileAtCoords(const TileCoords& tileCoordinates)
{
	return &GetTileAtIndex(GetIndexFromTileCoords(tileCoordinates));
}

Tile& Map::GetTileAtIndex(TileIndex index)
{
	return (m_tiles.at(index));
}

Tile* Map::GetTileAtWorldCoords(const WorldCoords& worldCoordinates)
{
	return &GetTileAtIndex(GetIndexFromTileCoords(GetTileCoordsFromWorldCoords(worldCoordinates)));
}

TileIndex Map::GetIndexFromTileCoords(const TileCoords& tileCoordinates) const
{
	return(m_size.x * tileCoordinates.y) + tileCoordinates.x;
}

TileCoords Map::GetTileCoordsFromIndex(int index) const
{
	int tileY = index / m_size.x;
	int tileX = index % m_size.x;
	return TileCoords(tileX, tileY);
}

WorldCoords Map::GetWorldCoordsFromTileCoords(const TileCoords& tileCoords)
{
	return WorldCoords(static_cast<float>(tileCoords.x), static_cast<float>(tileCoords.y));
}

TileCoords Map::GetTileCoordsFromWorldCoords(const WorldCoords& worldCoordinates) const
{
	return TileCoords(static_cast<int>(worldCoordinates.x), static_cast<int>(worldCoordinates.y));
}
