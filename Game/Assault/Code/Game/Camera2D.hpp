#pragma once
#include "Game/GameCommon.hpp"

class Tank;
class Vector2;

class Camera2D
{
public:
	Camera2D(Tank* Player);
	~Camera2D();	
	void Update(float deltaTime);
	void Render() const;
	void ShouldUpdate(bool shouldUpdate);
	void FollowPlayer(Tank* player);

private:
	WorldCoords m_position;
	Vector2 m_screenSize;
	Vector2 m_cameraCenteredOnScreenPosition;
	Vector2 m_previousPlayerPosition;
	float m_previousPlayerOrientation;
	float m_orientationDegrees;
	float m_numTilesInViewVertically;
	Tank* m_Player;
	bool m_shouldUpdate;
};
