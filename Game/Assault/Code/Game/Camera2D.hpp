#pragma once
#include "Game/GameCommon.hpp"

class Tank;
class Vector2;

class Camera2D
{
public:
	Camera2D(Tank* Player);
	~Camera2D();	
	void Update();
	void Render() const;

private:
	WorldCoords m_position;
	Vector2 m_screenSize;
	Vector2 m_cameraCenteredOnScreenPosition;
	float m_orientationDegrees;
	float m_numTilesInViewVertically;
	Tank* m_Player;
};
