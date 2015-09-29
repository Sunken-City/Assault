#include "Game/Camera2D.hpp"
#include "Game/Tank.hpp"

Camera2D::Camera2D(Tank* Player) 
: m_Player(Player)
, m_screenSize(16.f, 9.f)
, m_cameraCenteredOnScreenPosition(m_screenSize.x * 0.5f, m_screenSize.y * 0.2f)
, m_previousPlayerOrientation(0.f)
, m_previousPlayerPosition(0.f, 0.f)
, m_shouldUpdate(true)
{
}

Camera2D::~Camera2D()
{
}

void Camera2D::Update(float deltaTime)
{
	UNUSED(deltaTime);
	if (m_shouldUpdate)
	{
		m_previousPlayerPosition = m_Player->GetPosition();
		m_previousPlayerOrientation = m_Player->GetOrientation();
	}
}

void Camera2D::Render() const
{
	TheRenderer::instance->SetOrtho(Vector2(0.f, 0.f), m_screenSize);
	TheRenderer::instance->Translate(m_cameraCenteredOnScreenPosition);
	TheRenderer::instance->Rotate(-(m_previousPlayerOrientation - 90.f));
	TheRenderer::instance->Translate(m_previousPlayerPosition * -1.0f);
}

void Camera2D::ShouldUpdate(bool shouldUpdate)
{
	m_shouldUpdate = shouldUpdate;
}

void Camera2D::FollowPlayer(Tank* player)
{
	m_Player = player;
}
