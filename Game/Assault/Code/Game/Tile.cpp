#include "Game/Tile.hpp"
#include "Engine/Renderer/AABB2.hpp"

const float Tile::TILE_SIZE = 1.0f;
const float Tile::HALF_TILE_SIZE = TILE_SIZE / 2.f;

Tile::Tile() : m_tileCoords(0, 0), m_type(TileType::GRASS), m_color(RGBA(0.0f, 0.5f, 0.0f))
{
}

Tile::Tile(TileCoords position, TileType type) : m_tileCoords(position), m_type(type), m_color(GetColorFromType(type))
{

}

Tile::Tile(int x, int y, TileType type) : m_tileCoords(x, y), m_type(type), m_color(GetColorFromType(type))
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
	TheRenderer::instance->DrawAABB(AABB2(Vector2(0.0f, 0.0f), Vector2(TILE_SIZE, TILE_SIZE)), m_color);
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

RGBA Tile::GetColorFromType(TileType type)
{
	if (type == TileType::GRASS)
	{
		return RGBA(0.0f, 0.8f, 0.0f);
	}
	else if (type == TileType::STONE)
	{
		return RGBA(0.5f, 0.5f, 0.5f);
	}
	else
	{
		return RGBA(0.7f, 0.9f, 1.0f);
	}
}

TileType Tile::GetType() const
{
	return m_type;
}

