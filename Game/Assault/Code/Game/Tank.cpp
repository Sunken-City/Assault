#include "Game/Tank.hpp"
#include "Game/GameCommon.hpp"
#include "Engine/Renderer/Texture.hpp"
#include "Game/Map.hpp"
#include "Game/Tile.hpp"

const float Tank::BULLET_COOLDOWN = 0.4f;
const float Tank::DEGREES_PER_SECOND = 50.0f;
const float Tank::POSITION_PER_SECOND = 2.5f;
const float Tank::TANK_NOSE_LOCATION = 0.5f;
const float Tank::TANK_SIZE = 1.0f;

Tank::Tank(const Vector2& startingPosition, Map* map) : m_texture(Texture::CreateOrGetTexture("Data/Images/Tank.png")), m_map(map)
{
	m_color = RGBA(1.0f, 1.0f, 1.0f);
	m_boundingBox = AABB2(Vector2(0.f, 0.f), Vector2(TANK_SIZE, TANK_SIZE));
	m_position = startingPosition;
	m_orientation = 0.f;
	m_physicalRadius = TANK_SIZE / 2.3f;
	m_cosmeticRadius = TANK_SIZE / 1.7f;
	SetMaxHealth(10.f);
}

Tank::Tank(const Vector2& startingPosition, Map* map, const std::string& imageFilePath) : m_texture(Texture::CreateOrGetTexture(imageFilePath)), m_map(map)
{
	m_color = RGBA(1.0f, 1.0f, 1.0f);
	m_boundingBox = AABB2(Vector2(0.f, 0.f), Vector2(TANK_SIZE, TANK_SIZE));
	m_position = startingPosition;
	m_orientation = 0.f;
	m_physicalRadius = TANK_SIZE / 2.3f;
	m_cosmeticRadius = TANK_SIZE / 1.7f;
	SetMaxHealth(10.f);
}

Tank::~Tank()
{
}

void Tank::Update(float deltaTime)
{
	float healthRatio = (m_health / m_maxHealth);
	m_color = RGBA(1.0f, healthRatio, healthRatio);

	Entity::Update(deltaTime);

	CheckForTileCollisions();
}

void Tank::Render() const
{
	TheRenderer::instance->PushMatrix();

	TheRenderer::instance->Translate(m_position);
	TheRenderer::instance->Rotate(m_orientation);

	//Translate backwards half of the bounding box so we rotate around the center of the tank.
	TheRenderer::instance->Translate(m_boundingBox.maxs * -0.5);
	TheRenderer::instance->DrawTexturedAABB(m_boundingBox, Vector2(0.f, 0.f), Vector2(1.f, 1.f), *m_texture, m_color);

	TheRenderer::instance->PopMatrix();
	Entity::Render();
}

void Tank::FireBullet()
{

}

void Tank::CollideWith(Entity* ent)
{
	UNUSED(ent);
}

void Tank::CheckForTileCollisions()
{
	const TileCoords NORTH_NEIGHBOR = TileCoords(0, 1);
	const TileCoords SOUTH_NEIGHBOR = TileCoords(0, -1);
	const TileCoords WEST_NEIGHBOR = TileCoords(1, 0);
	const TileCoords EAST_NEIGHBOR = TileCoords(-1, 0);
	const TileCoords NORTHWEST_NEIGHBOR = TileCoords(1, 1);
	const TileCoords NORTHEAST_NEIGHBOR = TileCoords(-1, 1);
	const TileCoords SOUTHWEST_NEIGHBOR = TileCoords(1, -1);
	const TileCoords SOUTHEAST_NEIGHBOR = TileCoords(-1, -1);

	Tile* currentTile = m_map->GetTileAtWorldCoords(m_position);
	TileCoords currentTilePosition = currentTile->GetTileCoords();

	Tile* tileToCheck = m_map->GetTileAtCoords(currentTilePosition + NORTH_NEIGHBOR);
	if (tileToCheck->IsSolid())
	{
		float distanceInsideTile = ((m_position.y + m_physicalRadius) - tileToCheck->GetWorldCoordsFromTileMin().y);
		if (distanceInsideTile > 0.f)
		{
			m_position.y -= distanceInsideTile;
		}
	}

	//Edge Cases
	tileToCheck = m_map->GetTileAtCoords(currentTilePosition + SOUTH_NEIGHBOR);
	if (tileToCheck->IsSolid())
	{
		float distanceInsideTile = (currentTile->GetWorldCoordsFromTileMin().y - (m_position.y - m_physicalRadius));
		if (distanceInsideTile > 0.f)
		{
			m_position.y += distanceInsideTile;
		}
	}

	tileToCheck = m_map->GetTileAtCoords(currentTilePosition + WEST_NEIGHBOR);
	if (tileToCheck->IsSolid())
	{
		float distanceInsideTile = ((m_position.x + m_physicalRadius) - tileToCheck->GetWorldCoordsFromTileMin().x);
		if (distanceInsideTile > 0.f)
		{
			m_position.x -= distanceInsideTile;
		}
	}

	tileToCheck = m_map->GetTileAtCoords(currentTilePosition + EAST_NEIGHBOR);
	if (tileToCheck->IsSolid())
	{
		float distanceInsideTile = (currentTile->GetWorldCoordsFromTileMin().x - (m_position.x - m_physicalRadius));
		if (distanceInsideTile > 0.f)
		{
			m_position.x += distanceInsideTile;
		}
	}

	//Corner Cases
	tileToCheck = m_map->GetTileAtCoords(currentTilePosition + NORTHWEST_NEIGHBOR);
	if (tileToCheck->IsSolid())
	{
		WorldCoords cornerPoint = tileToCheck->GetWorldCoordsFromTileMin();
		if (MathUtils::IsPointInDisk(cornerPoint, m_position, m_physicalRadius))
		{
			CollideWithCorner(cornerPoint);
		}
	}

	tileToCheck = m_map->GetTileAtCoords(currentTilePosition + NORTHEAST_NEIGHBOR);
	if (tileToCheck->IsSolid())
	{
		WorldCoords cornerPoint = tileToCheck->GetWorldCoordsFromTileMin() + WorldCoords(1.0f, 0.0f);
		if (MathUtils::IsPointInDisk(cornerPoint, m_position, m_physicalRadius))
		{
			CollideWithCorner(cornerPoint);
		}
	}

	tileToCheck = m_map->GetTileAtCoords(currentTilePosition + SOUTHWEST_NEIGHBOR);
	if (tileToCheck->IsSolid())
	{
		WorldCoords cornerPoint = currentTile->GetWorldCoordsFromTileMin() + WorldCoords(1.0f, 0.0f);
		if (MathUtils::IsPointInDisk(cornerPoint, m_position, m_physicalRadius))
		{
			CollideWithCorner(cornerPoint);
		}
	}

	tileToCheck = m_map->GetTileAtCoords(currentTilePosition + SOUTHEAST_NEIGHBOR);
	if (tileToCheck->IsSolid())
	{
		WorldCoords cornerPoint = currentTile->GetWorldCoordsFromTileMin();
		if (MathUtils::IsPointInDisk(cornerPoint, m_position, m_physicalRadius))
		{
			CollideWithCorner(cornerPoint);
		}
	}
}

void Tank::CollideWithCorner(const WorldCoords& cornerPoint)
{
	Vector2 pushDir = m_position - cornerPoint;
	pushDir.Normalize(); //Normalize so that we can scale by the distance we need to get pushed.
	float distToCorner = MathUtils::CalcDistanceBetweenPoints(cornerPoint, m_position);
	float pushDist = m_physicalRadius - distToCorner;
	pushDir *= pushDist;
	m_position += pushDir;
}

WorldCoords Tank::GetNosePosition()
{
	Vector2 tankDirection = Vector2(cos(MathUtils::DegreesToRadians(m_orientation)), sin(MathUtils::DegreesToRadians(m_orientation)));
	Vector2 tankNoseDirection = tankDirection * TANK_NOSE_LOCATION;
	return m_position + tankNoseDirection;
}