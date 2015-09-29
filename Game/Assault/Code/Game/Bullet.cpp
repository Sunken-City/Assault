#include "Game/Bullet.hpp"
#include "Game/Map.hpp"
#include "Game/GameCommon.hpp"
#include "Engine/Renderer/Texture.hpp"
#include <math.h>

const float Bullet::BULLET_SIZE = 0.2f;

Bullet::Bullet(Map* map, const Vector2& spawnPosition, float parentOrientation, int factionNumber, float bulletSpeed, float lifespan) : m_texture(Texture::CreateOrGetTexture("Data/Images/Bullet.png"))
, m_bulletSpeed(bulletSpeed)
, m_lifespan(lifespan)
, m_map(map)
{
	m_isDead = false;
	m_faction = factionNumber;
	m_orientation = parentOrientation;
	m_angularVelocity = 0.0f;
	m_cosmeticRadius = BULLET_SIZE / 2.f;
	m_physicalRadius = BULLET_SIZE / 2.5f;
	m_boundingBox = AABB2(Vector2(0.f, 0.f), Vector2(BULLET_SIZE, BULLET_SIZE));
	m_color = RGBA(1.0f, 1.0f, 1.0f, 1.0f);
	Entity::SetMaxHealth(1.f);

	m_position = spawnPosition;
	Vector2 bulletDiretion = Vector2(cos(MathUtils::DegreesToRadians(m_orientation)), sin(MathUtils::DegreesToRadians(m_orientation)));
	m_velocity = (bulletDiretion * m_bulletSpeed);
	m_acceleration = Vector2(0.0f, 0.0f);
}

Bullet::~Bullet()
{

}

void Bullet::Update(float deltaTime)
{
	Entity::Update(deltaTime);
	m_colorTransitionFraction = m_ageInSeconds / m_lifespan;
	m_color = RGBA(1.0f, m_colorTransitionFraction, 0.0f, 1.0f);

	if (m_map->GetTileAtWorldCoords(m_position)->IsSolid())
	{
		m_isDead = true;
	}
}

void Bullet::Render() const
{
	TheRenderer::instance->PushMatrix();

	TheRenderer::instance->Translate(m_position);
	TheRenderer::instance->Rotate(m_orientation);
	TheRenderer::instance->Translate(m_boundingBox.maxs * -0.5);
	TheRenderer::instance->DrawTexturedAABB(m_boundingBox, Vector2(0.f, 0.f), Vector2(1.f, 1.f), *m_texture, m_color);

	TheRenderer::instance->PopMatrix();

	Entity::Render();
}

void Bullet::CollideWith(Entity* ent)
{
	this->TakeDamage(1.f);
	ent->TakeDamage(1.f);
}