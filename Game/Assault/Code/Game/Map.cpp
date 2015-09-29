#include "Game/Map.hpp"
#include "Game/GameCommon.hpp"
#include "Game/TheGame.hpp"
#include "Game/PlayerTank.hpp"
#include "Game/EnemyTank.hpp"
#include "Game/EnemyTurret.hpp"
#include "Game/Camera2D.hpp"
#include "Game/Bullet.hpp"

Map::Map(const TileCoords& size) : m_size(size)
{
	CreateTileDefinitions();

	//Map Generation
	TileCoords tankSpawnLocation;
	for (int y = 0; y < m_size.y; y++)
	{
		for (int x = 0; x < m_size.x; x++)
		{
			TileDefinition* type = &m_definitions[(int)TileType::GRASS];
			//If the tile is on the border, make it stone.
			if (y == 0 || x == 0 || y == m_size.y - 1 || x == m_size.x - 1)
			{
				type = &m_definitions[(int)TileType::STONE];
			}
			//Set a few tiles to stone inside
			else if (MathUtils::GetRandom(0, 10) == 1)
			{
				type = &m_definitions[(int)TileType::STONE];
			}
			//Set the last grass tile to be our spawn location.
			if (type == &m_definitions[(int)TileType::GRASS])
			{
				tankSpawnLocation = TileCoords(x, y);
			}
			m_tiles.push_back(Tile(x, y, type));
		}
	}
	PlayerTank* player = new PlayerTank(Map::GetWorldCoordsFromTileCoords(tankSpawnLocation), this);

	for (int i = 0; i < NUM_TURRETS; i++)
	{
		int lastTileIndex = m_tiles.size() - 1;
		Tile* selectedTile = &m_tiles[MathUtils::GetRandom(0, lastTileIndex)];
		while (selectedTile->IsSolid())
		{
			selectedTile = &m_tiles[MathUtils::GetRandom(0, lastTileIndex)];
		}
		WorldCoords turretSpawnLocation = selectedTile->GetWorldCoordsFromTileCenter();
		EnemyTurret* enemy = new EnemyTurret(turretSpawnLocation, this, player);
		m_entities.insert(enemy);
	}

	for (int i = 0; i < NUM_TANKS; i++)
	{
		int lastTileIndex = m_tiles.size() - 1;
		Tile* selectedTile = &m_tiles[MathUtils::GetRandom(0, lastTileIndex)];
		while (selectedTile->IsSolid())
		{
			selectedTile = &m_tiles[MathUtils::GetRandom(0, lastTileIndex)];
		}
		WorldCoords tankSpawnLocation = selectedTile->GetWorldCoordsFromTileCenter();
		EnemyTank* enemy = new EnemyTank(tankSpawnLocation, this, player);
		m_entities.insert(enemy);
	}

	m_entities.insert(player);
	m_Camera = new Camera2D(player);
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

	for (std::set<Bullet*>::iterator iter = m_bullets.begin(); iter != m_bullets.end(); ++iter)
	{
		Entity* gameObject = *iter;
		gameObject->Update(deltaTime);
	}

	for (std::set<Bullet*>::iterator bullet = m_bullets.begin(); bullet != m_bullets.end(); ++bullet)
	{
		for (std::set<Entity*>::iterator entity = m_entities.begin(); entity != m_entities.end(); ++entity)
		{
			Entity* bulletToCheck = *bullet;
			Entity* entityToCollideWith = *entity;
			if (bulletToCheck->GetFaction() != entityToCollideWith->GetFaction() && bulletToCheck->Overlaps(*entityToCollideWith))
			{
				bulletToCheck->CollideWith(entityToCollideWith);
			}
		}
	}

	for (std::set<Entity*>::iterator iter = m_entities.begin(); iter != m_entities.end(); ++iter)
	{
		Entity* gameObject = *iter;
		if (gameObject->IsDead())
		{
			iter = m_entities.erase(iter);
		}
		if (iter == m_entities.end())
		{
			break;
		}
	}

	for (std::set<Bullet*>::iterator iter = m_bullets.begin(); iter != m_bullets.end(); ++iter)
	{
		Bullet* gameObject = *iter;
		if (gameObject->IsDead())
		{
			iter = m_bullets.erase(iter);
		}
		if (iter == m_bullets.end())
		{
			break;
		}
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

	for (std::set<Bullet*>::iterator iter = m_bullets.begin(); iter != m_bullets.end(); ++iter)
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

bool Map::HasLineOfSight(const WorldCoords& start, const WorldCoords& end)
{
	Vector2 distance = end - start;
	Vector2 current = start;
	Vector2 step = distance * .01;
	for (int i = 0; i < 100; i++)
	{
		current += step;
		Tile* currentTile = GetTileAtCoords(GetTileCoordsFromWorldCoords(current));
		if (currentTile->IsSolid())
		{
			return false;
		}
	}
	return true;

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


void Map::CreateTileDefinitions()
{
	m_definitions.push_back(TileDefinition(TileType::GRASS, TileCoords(0, 0), RGBA(0.00f, 1.00f, 0.00f, 1.0f), false));
	m_definitions.push_back(TileDefinition(TileType::DIRT, TileCoords(1, 0), RGBA(0.58f, 0.30f, 0.00f, 1.0f), false));
	m_definitions.push_back(TileDefinition(TileType::STONE, TileCoords(1, 1), RGBA(0.50f, 0.50f, 0.50f, 1.0f), true));
}


void Map::SpawnBullet(const WorldCoords& position, float orientation, int factionNumber, float bulletSpeed, float lifespan)
{
	m_bullets.insert(new Bullet(this, position, orientation, factionNumber, bulletSpeed, lifespan));
}