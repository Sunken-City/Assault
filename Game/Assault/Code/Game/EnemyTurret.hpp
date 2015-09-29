#pragma once
#include "Game/Tank.hpp"
#include "Game/GameCommon.hpp"

class PlayerTank;

class EnemyTurret : public Tank
{
public:
	EnemyTurret(const Vector2& startingPosition, Map* map, PlayerTank* player);
	~EnemyTurret();
	virtual void Update(float deltaTime);
	virtual void Render() const;
	virtual void FireBullet();
	virtual void CollideWith(Entity* ent);

private:
	WorldCoords GetNosePosition();

	static const float BULLET_COOLDOWN;
	static const float FIRING_RANGE_DEGREES;
	static const float FIRING_RANGE_DISTANCE_SQUARED;
	static const float DEGREES_PER_SECOND;
	static const float POSITION_PER_SECOND;
	static const float TANK_NOSE_LOCATION;
	static const float TANK_SIZE;

	float m_timeSinceLastBullet;
	PlayerTank* m_player;

};
