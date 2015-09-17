#include "SpriteAnim.hpp"
#include "Engine/Renderer/AABB2.hpp"

SpriteAnim::~SpriteAnim()
{
}

void SpriteAnim::Update(float deltaSeconds)
{
	m_age += deltaSeconds;
}

bool SpriteAnim::IsDone()
{
	return !m_isDone;
}

void SpriteAnim::PlayFromStart()
{
	m_isDone = false;
	m_age = 0.f;
}

void SpriteAnim::StopPlaying()
{
	m_isDone = true;
}

// AABB2 SpriteAnim::GetCurrentTexCoords() const
// {
// 	Multiply m_age by fps instead lel
// 	(int)floor(m_age / m_secondsPerFrame);
// }
