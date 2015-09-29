#pragma once

#include "Engine/Renderer/AABB2.hpp"
#include "Engine/Renderer/RGBA.hpp"

class Vector2;

enum class type
{
	Bullet,
	Tank
};

class Entity
{
public:
	Entity();
	virtual ~Entity();
	virtual void Update(float deltaTime);
	virtual void Render() const;
	virtual void CollideWith(Entity* ent);

	bool Overlaps(const Entity& ent) const;
	Vector2 GetPosition() const;
	Vector2 GetVelocity() const;
	float GetOrientation() const;
	void TakeDamage(float damage);
	void SetMaxHealth(float maxHealth);
	bool IsDead() const;
	int GetFaction();

	static void ToggleDebugDraw();

	static const int PLAYER_FACTION = 0;
	static const int ENEMY_FACTION = 1;

protected:
	AABB2 m_boundingBox;
	RGBA m_color;
	Vector2 m_position;
	Vector2 m_velocity;
	Vector2 m_acceleration;

	float m_angularVelocity;
	float m_orientation;
	float m_physicalRadius;
	float m_cosmeticRadius;
	float m_ageInSeconds;
	float m_ageAtDeath;
	float m_maxHealth;
	float m_health;

	int m_faction;
	bool m_isDead;

	static bool m_displayDebugInfo;
};
