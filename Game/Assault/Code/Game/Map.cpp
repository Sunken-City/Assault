#include "Game/Map.hpp"
#include "Game/GameCommon.hpp"
#include "Game/TheGame.hpp"
#include "Game/PlayerTank.hpp"
#include "Game/EnemyTank.hpp"
#include "Game/EnemyTurret.hpp"
#include "Game/Camera2D.hpp"
#include "Game/Bullet.hpp"

XInputController Map::m_controller = XInputController(0); 
const float Map::TIME_TO_RESPAWN = 5.0f;

Map::Map(const TileCoords& size) : m_size(size), m_waitingForRespawn(false)
{
	CreateTileDefinitions();

	//Map Generation
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
				m_playerSpawn = TileCoords(x, y);
			}
			m_tiles.push_back(Tile(x, y, type));
		}
	}
	m_playerTank = new PlayerTank(Map::GetWorldCoordsFromTileCoords(m_playerSpawn), this, m_controller);

	for (int i = 0; i < NUM_TURRETS; i++)
	{
		int lastTileIndex = m_tiles.size() - 1;
		Tile* selectedTile = &m_tiles[MathUtils::GetRandom(0, lastTileIndex)];
		while (selectedTile->IsSolid())
		{
			selectedTile = &m_tiles[MathUtils::GetRandom(0, lastTileIndex)];
		}
		WorldCoords turretSpawnLocation = selectedTile->GetWorldCoordsFromTileCenter();
		EnemyTurret* enemy = new EnemyTurret(turretSpawnLocation, this, m_playerTank);
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
		EnemyTank* enemy = new EnemyTank(tankSpawnLocation, this, m_playerTank);
		m_entities.insert(enemy);
	}

	m_entities.insert(m_playerTank);
	m_Camera = new Camera2D(m_playerTank);
}

Map::~Map()
{
}

void Map::Update(float deltaTime)
{
	m_controller.Update(deltaTime);
	if ((m_controller.JustPressed(XboxButton::START) || TheApp::instance->WasKeyJustPressed('P')) && !m_waitingForRespawn)
	{
		TheGame::instance->TogglePause();
	}

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

	if (m_playerTank && m_playerTank->IsDead())
	{
		m_playerTank = nullptr;
		m_Camera->ShouldUpdate(false);
		m_waitingForRespawn = true;
	}

	if (m_waitingForRespawn)
	{
		playerTankTimeSinceDeath += deltaTime;
		if (playerTankTimeSinceDeath > TIME_TO_RESPAWN)
		{
			TheGame::instance->TogglePause();
			m_waitingForRespawn = false;
			playerTankTimeSinceDeath = 0.f;
		}
	}

	for (std::set<Entity*>::iterator iter = m_entities.begin(); iter != m_entities.end(); ++iter)
	{
		Entity* gameObject = *iter;
		if (gameObject->IsDead())
		{
			delete gameObject;
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
			delete gameObject;
			iter = m_bullets.erase(iter);
		}
		if (iter == m_bullets.end())
		{
			break;
		}
	}
	m_Camera->Update(deltaTime);
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
	Vector2 step = distance * .01f;
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

void Map::RespawnTank()
{
	if (!m_playerTank)
	{
		m_playerTank = new PlayerTank(Map::GetWorldCoordsFromTileCoords(m_playerSpawn), this, m_controller);
		m_entities.insert(m_playerTank);
		m_Camera->ShouldUpdate(true);
		m_Camera->FollowPlayer(m_playerTank);
	}
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