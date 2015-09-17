#pragma once
#include "Engine/Renderer/SpriteSheet.hpp"

class AABB2;

enum class AnimTypes
{
	ONE_SHOT,
	LOOP,
	PING_PONG
};

class SpriteAnim
{
public:
	SpriteAnim(const SpriteSheet& sheet, float seconds, int startSpriteIndex, int endSpriteIndex);
	~SpriteAnim();

	void Update(float deltaSeconds);
	bool IsDone();
	void PlayFromStart();
	void StopPlaying();

	AABB2 GetCurrentTexCoords() const;

private:
	const SpriteSheet& m_sheet;
	float m_age;
	float m_secondsPerFrame;
	bool m_isDone;
	SpriteAnim& operator=(const SpriteAnim&);
};
