#pragma once
#include "Game/Tank.hpp"
#include "Game/GameCommon.hpp"

class PlayerTank : public Tank
{
public:
	PlayerTank(const Vector2& startingPosition, Map* map);
	~PlayerTank();
	virtual void Update(float deltaTime);
	virtual void Render() const;
	virtual void FireBullet();
	virtual void CollideWith(Entity* ent);

private:

	void UpdateFromController(float deltaTime);
	WorldCoords GetNosePosition();

	static XInputController m_controller;
	static const float BULLET_COOLDOWN;
	static const float DEGREES_PER_SECOND;
	static const float POSITION_PER_SECOND;
	static const float TANK_NOSE_LOCATION;
	static const float TANK_SIZE;

	float m_timeSinceLastBullet;

};
