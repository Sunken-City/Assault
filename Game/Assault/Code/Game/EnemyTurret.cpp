#include "EnemyTurret.hpp"
#include "PlayerTank.hpp"
#include "Map.hpp"
#include <math.h>

const float EnemyTurret::BULLET_COOLDOWN = 2.0f;
const float EnemyTurret::FIRING_RANGE_DEGREES = 5.0f;
const float EnemyTurret::FIRING_RANGE_DISTANCE_SQUARED = 20.0f * 2.0f;
const float EnemyTurret::DEGREES_PER_SECOND = 90.0f;
const float EnemyTurret::POSITION_PER_SECOND = 2.5f;
const float EnemyTurret::TANK_NOSE_LOCATION = 0.5f;
const float EnemyTurret::TANK_SIZE = 1.0f;

EnemyTurret::EnemyTurret(const Vector2& startingPosition, Map* map, PlayerTank* player) : Tank(startingPosition, map, "Data/Images/EnemyTurret.png"), m_timeSinceLastBullet(0.f), m_player(player)
{
	m_faction = Entity::ENEMY_FACTION;
	Entity::SetMaxHealth(3.f);
}

EnemyTurret::~EnemyTurret()
{
}

void EnemyTurret::Update(float deltaTime)
{
	m_timeSinceLastBullet += deltaTime;
	Vector2 playerPosition = m_player->GetPosition();
	if ((MathUtils::CalcDistSquaredBetweenPoints(playerPosition, m_position) < FIRING_RANGE_DISTANCE_SQUARED)
		&& m_map->HasLineOfSight(m_position, playerPosition))
	{
		float goalAngle = MathUtils::RadiansToDegrees(atan2(playerPosition.y - m_position.y, playerPosition.x - m_position.x));
		float m_adjustment = MathUtils::CalcShortestAngularDisplacement(m_orientation, goalAngle);
		float turnDegreesThisFrame = DEGREES_PER_SECOND * deltaTime;

		m_orientation += MathUtils::Clamp(m_adjustment, -turnDegreesThisFrame, turnDegreesThisFrame);
		if (m_timeSinceLastBullet > BULLET_COOLDOWN && abs(m_adjustment) < FIRING_RANGE_DEGREES)
		{
			FireBullet();
			m_timeSinceLastBullet = 0.f;
		}
		
	}
	Tank::Update(deltaTime);
}

void EnemyTurret::Render() const
{
	Tank::Render();
}

WorldCoords EnemyTurret::GetNosePosition()
{
	Vector2 tankDirection = Vector2(cos(MathUtils::DegreesToRadians(m_orientation)), sin(MathUtils::DegreesToRadians(m_orientation)));
	Vector2 tankNoseDirection = tankDirection * TANK_NOSE_LOCATION;
	return m_position + tankNoseDirection;
}

void EnemyTurret::FireBullet()
{
	m_map->SpawnBullet(GetNosePosition(), m_orientation, m_faction, 4.0f, 2.0f);
}

void EnemyTurret::CollideWith(Entity* ent)
{
	UNUSED(ent);
}
