#include "Game/Camera2D.hpp"
#include "Game/Tank.hpp"

Camera2D::Camera2D(Tank* Player) : m_Player(Player), m_screenSize(16.f, 9.f), m_cameraCenteredOnScreenPosition(m_screenSize.x * 0.5f, m_screenSize.y * 0.2f)
{
}

Camera2D::~Camera2D()
{
}

void Camera2D::Update()
{
	
}

void Camera2D::Render() const
{
	TheRenderer::instance->SetOrtho(Vector2(0.f, 0.f), m_screenSize);
	TheRenderer::instance->Translate(m_cameraCenteredOnScreenPosition);
	TheRenderer::instance->Rotate(-(m_Player->GetOrientation() - 90.f));
	TheRenderer::instance->Translate(m_Player->GetPosition() * -1.0f);
}
