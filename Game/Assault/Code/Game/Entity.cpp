#include "Game/Entity.hpp"
#include "Game/GameCommon.hpp"
#include "Game/TheApp.hpp"
#include <math.h>

bool Entity::m_displayDebugInfo = false;

Entity::Entity()
: m_position(Vector2(0.0f, 0.0f))
, m_velocity(Vector2(0.0f, 0.0f))
, m_acceleration(Vector2(0.0f, 0.0f))
, m_orientation(0.0f)
, m_angularVelocity(0.0f)
, m_ageInSeconds(0.0f)
, m_isDead(false)
, m_maxHealth(10.f)
, m_health(m_maxHealth)
, m_physicalRadius(0.0f)
, m_cosmeticRadius(0.0f)
, m_faction(ENEMY_FACTION)
{
}

Entity::~Entity()
{
}

void Entity::Update(float deltaTime)
{
	m_velocity += m_acceleration * deltaTime;
	m_position += m_velocity * deltaTime;
	m_orientation += m_angularVelocity * deltaTime;
	m_ageInSeconds += deltaTime;
}

void Entity::Render() const
{
	if (m_displayDebugInfo)
	{
		TheRenderer::instance->SetColor(0.0f, 1.0f, 1.0f, 1.0f);

		TheRenderer::instance->SetPointSize(3);
		TheRenderer::instance->DrawPoint(m_position);
		TheRenderer::instance->SetPointSize(1);

		TheRenderer::instance->SetColor(1.0f, 1.0f, 0.0f, 1.0f);
		Vector2 orientation = m_position + Vector2(cos(MathUtils::DegreesToRadians(m_orientation)), sin(MathUtils::DegreesToRadians(m_orientation)));
		TheRenderer::instance->DrawLine(m_position, orientation, 1.f);

		TheRenderer::instance->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
		TheRenderer::instance->DrawPolygonOutline(m_position, m_physicalRadius, TheRenderer::CIRCLE_SIDES, 0.0f);

		TheRenderer::instance->SetColor(0.0f, 0.0f, 1.0f, 1.0f);
		TheRenderer::instance->DrawPolygonOutline(m_position, m_cosmeticRadius, TheRenderer::CIRCLE_SIDES, 0.0f);

		TheRenderer::instance->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
}

bool Entity::Overlaps(const Entity& ent) const
{
	return MathUtils::DoDiscsOverlap(this->m_position, this->m_physicalRadius, ent.m_position, ent.m_physicalRadius);
}

Vector2 Entity::GetPosition() const
{
	return m_position;
}

Vector2 Entity::GetVelocity() const
{
	return m_velocity;
}

float Entity::GetOrientation() const
{
	return m_orientation;
}


void Entity::TakeDamage(float damage)
{
	m_health = MathUtils::Clamp(m_health - damage, 0.f, m_maxHealth);
	if (m_health <= 0.f)
	{
		m_isDead = true;
	}
}


void Entity::SetMaxHealth(float maxHealth)
{
	m_maxHealth = maxHealth;
	m_health = maxHealth;
}

bool Entity::IsDead() const
{
	return m_isDead;
}


int Entity::GetFaction()
{
	return m_faction;
}

void Entity::CollideWith(Entity* ent)
{
	UNUSED(ent);
}

void Entity::ToggleDebugDraw()
{
	m_displayDebugInfo = !m_displayDebugInfo;
}