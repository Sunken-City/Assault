#include "Game/TheGame.hpp"
#include "Game/GameCommon.hpp"
#include "Game/Map.hpp"
#include <math.h>

TheGame* TheGame::instance = nullptr;
//Map* TheGame::m_map = nullptr; // #Eiserloh: Never construct objects of significance before WinMain(). // new Map(TileCoords(20, 20));


TheGame::TheGame()
: m_map( nullptr )
{
	srand(0xDEADBEEF);
	m_map = new Map( TileCoords( 20, 20 ) ); // #Eiserloh: Construct the map (and all significant objects) at a controlled, deliberate time
}

TheGame::~TheGame()
{

}

int TheGame::GetRandom(int minimum, int maximum)
{
	return rand() % maximum + minimum;
}

void TheGame::Update(float deltaTime)
{
	m_map->Update(deltaTime);
}

void TheGame::Render() const
{
	m_map->Render();
}
