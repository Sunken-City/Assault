#include "Game/TheGame.hpp"
#include "Game/GameCommon.hpp"
#include "Game/Map.hpp"

TheGame* TheGame::instance = nullptr;

TheGame::TheGame()
: m_map( nullptr )
{
	srand(0xDEADBEEF);
	m_map = new Map( TileCoords( 40, 40 ) );
}

TheGame::~TheGame()
{

}

void TheGame::Update(float deltaTime)
{
	m_map->Update(deltaTime);
}

void TheGame::Render() const
{
	m_map->Render();
}