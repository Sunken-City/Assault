#include "Game/TheGame.hpp"
#include "Game/GameCommon.hpp"
#include "Game/Map.hpp"
#include "Engine/Renderer/AABB2.hpp"
#include "Engine/Renderer/Texture.hpp"

TheGame* TheGame::instance = nullptr;

TheGame::TheGame()
: m_map(nullptr)
, m_isPaused(false)
, m_pauseTexture(Texture::CreateOrGetTexture("Data/Images/Pause.png"))
{
	srand(0xDEADBEEF);
	m_map = new Map( TileCoords( 40, 40 ) );
}

TheGame::~TheGame()
{

}

void TheGame::Update(float deltaTime)
{
	if (m_isPaused)
	{
		deltaTime = 0.f;
	}
	m_map->Update(deltaTime);
}

void TheGame::Render() const
{
	m_map->Render();
	if (m_isPaused)
	{
		Vector2 screenMins = Vector2(0.f, 0.f);
		Vector2 screenMaxs = Vector2(TheApp::instance->GetWindowWidth(), TheApp::instance->GetWindowHeight());
		Vector2 gameMaxs = Vector2(16.f, 9.f);
		Vector2 pauseGraphicMins = Vector2(TheApp::instance->GetWindowWidth() / 8.f, TheApp::instance->GetWindowHeight() / 8.f);
		Vector2 pauseGraphicMaxs = Vector2(TheApp::instance->GetWindowWidth() * (7.f / 8.f), TheApp::instance->GetWindowHeight() * (7.f / 8.f));
		RGBA pauseColor = RGBA(0.0f, 0.0f, 0.0f, 0.3f);

		TheRenderer::instance->PushMatrix();
		TheRenderer::instance->DrawAABB(AABB2(screenMins, screenMaxs), pauseColor);
		TheRenderer::instance->SetOrtho(screenMins, screenMaxs);
		TheRenderer::instance->DrawTexturedAABB(AABB2(pauseGraphicMins, pauseGraphicMaxs), Vector2(0.f, 0.f), Vector2(1.f, 1.f), *m_pauseTexture, RGBA(1.f, 1.f, 1.f));
		TheRenderer::instance->SetOrtho(screenMins, gameMaxs);
		TheRenderer::instance->PopMatrix();
	}
}

void TheGame::TogglePause()
{
	m_isPaused = !m_isPaused;
	if (!m_isPaused)
	{
		m_map->RespawnTank();
	}
}

bool TheGame::IsPaused()
{
	return m_isPaused;
}
