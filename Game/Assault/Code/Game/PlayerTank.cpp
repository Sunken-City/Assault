#include "PlayerTank.hpp"
#include "Map.hpp"
#include "TheGame.hpp"

const float PlayerTank::BULLET_COOLDOWN = 0.3f;
const float PlayerTank::DEGREES_PER_SECOND = 50.0f;
const float PlayerTank::POSITION_PER_SECOND = 2.5f;
const float PlayerTank::TANK_NOSE_LOCATION = 0.5f;
const float PlayerTank::TANK_SIZE = 1.0f;

PlayerTank::PlayerTank(const Vector2& startingPosition, Map* map, const XInputController& controller) 
: Tank(startingPosition, map), m_timeSinceLastBullet(BULLET_COOLDOWN), m_controller(controller)
{
	m_faction = Entity::PLAYER_FACTION;
	Entity::SetMaxHealth(10.f);
}

PlayerTank::~PlayerTank()
{
	m_map->playerTankTimeSinceDeath = 0.f;
}

void PlayerTank::Update(float deltaTime)
{
	m_controller.Update(deltaTime);
	if (TheApp::instance->WasKeyJustPressed('H'))
	{
		TakeDamage(1.f);
	}

	if (TheApp::instance->WasKeyJustPressed('G'))
	{
		Entity::ToggleDebugDraw();
	}

	UpdateFromController(deltaTime);

	Tank::Update(deltaTime);
}

void PlayerTank::Render() const
{
	Tank::Render();

}

void PlayerTank::UpdateFromController(float deltaTime)
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

	m_timeSinceLastBullet += deltaTime;

	if ((m_controller.GetRightTrigger() > 128 || TheApp::instance->WasKeyJustPressed(' ')) 
		&& m_timeSinceLastBullet > BULLET_COOLDOWN 
		&& !TheGame::instance->IsPaused())
	{
		FireBullet();
		m_timeSinceLastBullet = 0.f;
	}
}

WorldCoords PlayerTank::GetNosePosition()
{
	Vector2 tankDirection = Vector2(cos(MathUtils::DegreesToRadians(m_orientation)), sin(MathUtils::DegreesToRadians(m_orientation)));
	Vector2 tankNoseDirection = tankDirection * TANK_NOSE_LOCATION;
	return m_position + tankNoseDirection;
}

void PlayerTank::FireBullet()
{
	m_map->SpawnBullet(GetNosePosition(), m_orientation, m_faction, 10.0f, 0.5f);
}

void PlayerTank::CollideWith(Entity* ent)
{
	UNUSED(ent);
}
