#pragma once

class Map;
class Texture;

class TheGame
{
public:
	TheGame();
	~TheGame();
	void Update(float deltaTime);
	void Render() const;
	void TogglePause();
	bool IsPaused();
	static TheGame* instance;

private:
	Map* m_map;
	Texture* m_pauseTexture;
	bool m_isPaused;
};
