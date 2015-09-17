#pragma once

class Map;

class TheGame
{
public:
	TheGame();
	~TheGame();
	void Update(float deltaTime);
	void Render() const;
	static int GetRandom(int minimum, int maximum);

	static TheGame* instance;

private:
	Map* m_map;

};
