#pragma once

#include "Engine/Renderer/AABB2.hpp"
#include "Engine/Renderer/RGBA.hpp"

class Vector2;

class Entity
{
public:
	Entity();
	~Entity();
	virtual void Update(float deltaTime);
	virtual void Render() const;
	bool Overlaps(const Entity& ent) const;
	Vector2 GetPosition() const;
	Vector2 GetVelocity() const;
	float GetOrientation() const;
	bool IsDead() const;

	static void ToggleDebugDraw();

protected:
	AABB2 m_boundingBox;
	RGBA m_color;
	Vector2 m_position;
	Vector2 m_velocity;
	Vector2 m_acceleration;

	float m_angularVelocity;
	float m_orientation;
	float m_physicalRadius;
	float m_ageInSeconds;
	float m_ageAtDeath;

	bool m_isDead;

	static bool m_displayDebugInfo;
};
