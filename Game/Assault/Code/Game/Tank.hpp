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
	~Tank();
	void Update(float deltaTime);
	void Render() const;

	Texture* GetTexture();
	void SetTexture(Texture* texture);

private:
	void UpdateFromController(float deltaTime);
	void CheckForTileCollisions();
	void CollideWithCorner(const WorldCoords& cornerPoint);
	static XInputController m_controller;
	static const float DEGREES_PER_SECOND;
	static const float POSITION_PER_SECOND;

	Texture* m_texture;
	Map* m_map;
};
