#pragma once
#include "Game/Entity.hpp"

class Vector2;
class Map;
class Texture;

class Bullet : public Entity
{
public:
	Bullet(Map* map, const Vector2& spawnPosition, float parentOrientation, int factionNumber, float bulletSpeed, float lifespan);
	~Bullet();

	void Update(float deltaTime);
	void Render() const;
	void CollideWith(Entity* ent);


private:
	static const float BULLET_SIZE;
	float m_bulletSpeed;
	float m_colorTransitionFraction;
	float m_lifespan;

	Map* m_map;
	Texture* m_texture;
};