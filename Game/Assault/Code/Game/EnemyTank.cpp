#include "EnemyTank.hpp"
#include "PlayerTank.hpp"
#include "Map.hpp"

const float EnemyTank::BULLET_COOLDOWN = 2.0f;
const float EnemyTank::DRIVING_RANGE_DEGREES = 45.0f;
const float EnemyTank::FIRING_RANGE_DEGREES = 5.0f;
const float EnemyTank::FIRING_RANGE_DISTANCE_SQUARED = 15.0f * 2.0f;
const float EnemyTank::DEGREES_PER_SECOND = 50.0f;
const float EnemyTank::POSITION_PER_SECOND = 0.5f;
const float EnemyTank::TANK_NOSE_LOCATION = 0.5f;
const float EnemyTank::TANK_SIZE = 1.0f;
const float EnemyTank::TIME_BETWEEN_DIRECTION_CHANGES_SECONDS = 3.0f;

EnemyTank::EnemyTank(const Vector2& startingPosition, Map* map, PlayerTank* player) 
: Tank(startingPosition, map, "Data/Images/EnemyTank.png")
, m_timeSinceLastBullet(0.f)
, m_player(player)
, m_timeSinceLastDirectionChange(TIME_BETWEEN_DIRECTION_CHANGES_SECONDS)
, m_goalAngle(m_orientation)
{
	m_faction = Entity::ENEMY_FACTION;
	Entity::SetMaxHealth(3.f);
}

EnemyTank::~EnemyTank()
{
}

void EnemyTank::Update(float deltaTime)
{
	m_timeSinceLastBullet += deltaTime;
	m_timeSinceLastDirectionChange += deltaTime;
	Vector2 playerPosition = m_player->GetPosition();

	if ((MathUtils::CalcDistSquaredBetweenPoints(playerPosition, m_position) < FIRING_RANGE_DISTANCE_SQUARED)
		 && m_map->HasLineOfSight(m_position, playerPosition))
	{
		m_velocity = Vector2(0.f, 0.f);
		m_goalAngle = MathUtils::RadiansToDegrees(atan2(playerPosition.y - m_position.y, playerPosition.x - m_position.x));
		float m_adjustment = MathUtils::CalcShortestAngularDisplacement(m_orientation, m_goalAngle);
		float turnDegreesThisFrame = DEGREES_PER_SECOND * deltaTime;

		m_orientation += MathUtils::Clamp(m_adjustment, -turnDegreesThisFrame, turnDegreesThisFrame);

		if (abs(m_adjustment) < DRIVING_RANGE_DEGREES)
		{
			Vector2 driveDirection = Vector2(cos(MathUtils::DegreesToRadians(m_orientation)), sin(MathUtils::DegreesToRadians(m_orientation)));
			m_velocity = (driveDirection * POSITION_PER_SECOND);
		}

		if (m_timeSinceLastBullet > BULLET_COOLDOWN && abs(m_adjustment) < FIRING_RANGE_DEGREES)
		{
			FireBullet();
			m_timeSinceLastBullet = 0.f;
		}

	}
	else
	{
		if (m_timeSinceLastDirectionChange > 3.0f)
		{
			m_goalAngle = MathUtils::GetRandomFromZeroTo(360.f);
			m_timeSinceLastDirectionChange = 0.f;
		}
		float m_adjustment = MathUtils::CalcShortestAngularDisplacement(m_orientation, m_goalAngle);
		float turnDegreesThisFrame = DEGREES_PER_SECOND * deltaTime;
		m_orientation += MathUtils::Clamp(m_adjustment, -turnDegreesThisFrame, turnDegreesThisFrame);	

		Vector2 driveDirection = Vector2(cos(MathUtils::DegreesToRadians(m_orientation)), sin(MathUtils::DegreesToRadians(m_orientation)));
		m_velocity = (driveDirection * POSITION_PER_SECOND);
	}
	Tank::Update(deltaTime);
}

void EnemyTank::Render() const
{
	Tank::Render();
}

WorldCoords EnemyTank::GetNosePosition()
{
	Vector2 tankDirection = Vector2(cos(MathUtils::DegreesToRadians(m_orientation)), sin(MathUtils::DegreesToRadians(m_orientation)));
	Vector2 tankNoseDirection = tankDirection * TANK_NOSE_LOCATION;
	return m_position + tankNoseDirection;
}

void EnemyTank::FireBullet()
{
	m_map->SpawnBullet(GetNosePosition(), m_orientation, m_faction, 4.0f, 2.0f);
}

void EnemyTank::CollideWith(Entity* ent)
{
	UNUSED(ent);
}
