#pragma once

#include <map>
#include "Engine/Math/Vector2Int.hpp"

class Texture
{
public:
	static Texture* GetTextureByName(const std::string& imageFilePath);
	static Texture* CreateOrGetTexture(const std::string& imageFilePath);
	int m_openglTextureID;
	Vector2Int m_texelSize;

private:
	Texture(const std::string& imageFilePath);
	static std::map<std::string, Texture*> s_textureRegistry;
};
