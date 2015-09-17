#include "Game/Tank.hpp"
#include "Game/GameCommon.hpp"
#include "Engine/Renderer/Texture.hpp"
#include "Game/Map.hpp"
#include "Game/Tile.hpp"

XInputController Tank::m_controller = XInputController(0);

const float Tank::DEGREES_PER_SECOND = 50.0f;
const float Tank::POSITION_PER_SECOND = 2.5f;

Tank::Tank(const Vector2& startingPosition, Map* map) : m_texture(Texture::CreateOrGetTexture("Data/Images/Tank.png")), m_map(map)
{
	m_color = RGBA(1.0f, 0.f, 0.f);
	m_boundingBox = AABB2(Vector2(0.f, 0.f), Vector2(1.0f, 1.0f));
	m_position = startingPosition;
	m_orientation = 0.f;
	m_physicalRadius = 0.5f;
}

Tank::~Tank()
{
}

void Tank::Update(float deltaTime)
{
	m_controller.Update(deltaTime);

	if (TheApp::instance->IsKeyDown('A'))
	{
		m_orientation -= DEGREES_PER_SECOND * deltaTime;
	}
	else if (TheApp::instance->IsKeyDown('D'))
	{
		m_orientation += DEGREES_PER_SECOND * deltaTime;
	}
	if (TheApp::instance->IsKeyDown('W'))
	{
		m_position.y += POSITION_PER_SECOND * deltaTime;
	}
	else if (TheApp::instance->IsKeyDown('S'))
	{
		m_position.y -= POSITION_PER_SECOND * deltaTime;
	}

	UpdateFromController(deltaTime);

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

Texture* Tank::GetTexture()
{
	return m_texture;
}

void Tank::SetTexture(Texture* texture)
{
	m_texture = texture;
}

void Tank::UpdateFromController(float deltaTime)
{
	Vector2 leftStickDirection = m_controller.GetLeftStickPosition();
	Vector2 rightStickDirection = m_controller.GetRightStickPosition();

	if (leftStickDirection.CalculateMagnitude() > XInputController::DEADZONE || rightStickDirection.CalculateMagnitude() > XInputController::DEADZONE)
	{
		Vector2 newVelocity = Vector2(POSITION_PER_SECOND * cos(MathUtils::DegreesToRadians(m_orientation)), POSITION_PER_SECOND * sin(MathUtils::DegreesToRadians(m_orientation)));
		m_velocity = (newVelocity * leftStickDirection.y * 0.5f) + (newVelocity * rightStickDirection.y * 0.5f);

		m_orientation -= DEGREES_PER_SECOND * deltaTime * leftStickDirection.y;
		m_orientation += DEGREES_PER_SECOND * deltaTime * rightStickDirection.y;
	}
	else
	{
		m_velocity = Vector2(0.0f, 0.0f);
	}
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
	if (tileToCheck->GetType() == TileType::STONE)
	{
		float distanceInsideTile = ((m_position.y + m_physicalRadius) - tileToCheck->GetWorldCoordsFromTileMin().y);
		if (distanceInsideTile > 0.f)
		{
			m_position.y -= distanceInsideTile;
		}
	}

	//Edge Cases
	tileToCheck = m_map->GetTileAtCoords(currentTilePosition + SOUTH_NEIGHBOR);
	if (tileToCheck->GetType() == TileType::STONE)
	{
		float distanceInsideTile = (currentTile->GetWorldCoordsFromTileMin().y - (m_position.y - m_physicalRadius));
		if (distanceInsideTile > 0.f)
		{
			m_position.y += distanceInsideTile;
		}
	}

	tileToCheck = m_map->GetTileAtCoords(currentTilePosition + WEST_NEIGHBOR);
	if (tileToCheck->GetType() == TileType::STONE)
	{
		float distanceInsideTile = ((m_position.x + m_physicalRadius) - tileToCheck->GetWorldCoordsFromTileMin().x);
		if (distanceInsideTile > 0.f)
		{
			m_position.x -= distanceInsideTile;
		}
	}

	tileToCheck = m_map->GetTileAtCoords(currentTilePosition + EAST_NEIGHBOR);
	if (tileToCheck->GetType() == TileType::STONE)
	{
		float distanceInsideTile = (currentTile->GetWorldCoordsFromTileMin().x - (m_position.x - m_physicalRadius));
		if (distanceInsideTile > 0.f)
		{
			m_position.x += distanceInsideTile;
		}
	}

	//Corner Cases
	tileToCheck = m_map->GetTileAtCoords(currentTilePosition + NORTHWEST_NEIGHBOR);
	if (tileToCheck->GetType() == TileType::STONE)
	{
		WorldCoords cornerPoint = tileToCheck->GetWorldCoordsFromTileMin();
		if (MathUtils::IsPointInDisk(cornerPoint, m_position, m_physicalRadius))
		{
			CollideWithCorner(cornerPoint);
		}
	}

	tileToCheck = m_map->GetTileAtCoords(currentTilePosition + NORTHEAST_NEIGHBOR);
	if (tileToCheck->GetType() == TileType::STONE)
	{
		WorldCoords cornerPoint = tileToCheck->GetWorldCoordsFromTileMin() + WorldCoords(1.0f, 0.0f);
		if (MathUtils::IsPointInDisk(cornerPoint, m_position, m_physicalRadius))
		{
			CollideWithCorner(cornerPoint);
		}
	}

	tileToCheck = m_map->GetTileAtCoords(currentTilePosition + SOUTHWEST_NEIGHBOR);
	if (tileToCheck->GetType() == TileType::STONE)
	{
		WorldCoords cornerPoint = currentTile->GetWorldCoordsFromTileMin() + WorldCoords(1.0f, 0.0f);
		if (MathUtils::IsPointInDisk(cornerPoint, m_position, m_physicalRadius))
		{
			CollideWithCorner(cornerPoint);
		}
	}

	tileToCheck = m_map->GetTileAtCoords(currentTilePosition + SOUTHEAST_NEIGHBOR);
	if (tileToCheck->GetType() == TileType::STONE)
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
