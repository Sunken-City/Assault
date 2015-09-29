#pragma once
#include "Engine/Input/XInputController.hpp"
#include "Game/GameCommon.hpp"
#include "Game/Entity.hpp"

class Texture;
class Map;

class Tank : public Entity
{
public:
	Tank(const Vector2& startingPosition, Map* map);
	Tank(const Vector2& startingPosition, Map* map, const std::string& imageFilePath);
	virtual ~Tank();
	virtual void Update(float deltaTime);
	virtual void Render() const;
	virtual void FireBullet();
	virtual void CollideWith(Entity* ent);

protected:

	void CheckForTileCollisions();
	void CollideWithCorner(const WorldCoords& cornerPoint);
	virtual WorldCoords GetNosePosition();

	static const float BULLET_COOLDOWN;
	static const float DEGREES_PER_SECOND;
	static const float POSITION_PER_SECOND;
	static const float TANK_NOSE_LOCATION;
	static const float TANK_SIZE;

	Texture* m_texture;
	Map* m_map;
};
