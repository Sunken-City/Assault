#include "Game/Tile.hpp"
#include "Engine/Renderer/AABB2.hpp"
#include "Engine/Renderer/Texture.hpp"

const float Tile::TILE_SIZE = 1.0f;
const float Tile::HALF_TILE_SIZE = TILE_SIZE / 2.f;

Tile::Tile(TileCoords position, TileDefinition* definition) : m_tileCoords(position), m_definition(definition)
{

}

Tile::Tile(int x, int y, TileDefinition* definition) : m_tileCoords(x, y), m_definition(definition)
{

}

Tile::~Tile()
{
}

void Tile::Update(float deltaTime)
{
	//We don't need to do anything with this method just yet, but the signature has to match the calling convention.
	//I'd rather not introduce a potential bug into my code by modifying it and instead refactor when I can add functionality.
	deltaTime = 0;
}

void Tile::Render() const
{
	TheRenderer::instance->PushMatrix();
	TheRenderer::instance->Translate(GetWorldCoordsFromTileMin());
	AABB2 TextureCoords = m_definition->GetTextureCoordinates();
	TheRenderer::instance->DrawTexturedAABB(AABB2(Vector2(0.0f, 0.0f), Vector2(TILE_SIZE, TILE_SIZE)), TextureCoords.mins, TextureCoords.maxs, *m_definition->GetTexture(), m_definition->GetColor());
	TheRenderer::instance->PopMatrix();
}

TileCoords Tile::GetTileCoords() const
{
	return m_tileCoords;
}

WorldCoords Tile::GetWorldCoordsFromTileMin() const
{
	return WorldCoords(static_cast<float>(m_tileCoords.x), static_cast<float>(m_tileCoords.y));
}

WorldCoords Tile::GetWorldCoordsFromTileCenter() const
{
	return WorldCoords(static_cast<float>(m_tileCoords.x) + HALF_TILE_SIZE, static_cast<float>(m_tileCoords.y) + HALF_TILE_SIZE);
}

TileType Tile::GetType() const
{
	return m_definition->GetType();
}

bool Tile::IsSolid() const
{
	return m_definition->IsSolid();
}

