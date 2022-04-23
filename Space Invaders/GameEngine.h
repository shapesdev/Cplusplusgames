#pragma once
#include <SFML/Graphics.hpp>
#include "ScreenManager.h"
#include "SoundEngine.h"

using namespace sf;

class GameEngine
{
public:
	GameEngine();

	SoundEngine m_SoundEngine;
	void Run();

private:
	Clock m_Clock;
	Time m_DT;
	RenderWindow m_Window;

	unique_ptr<ScreenManager> m_ScreenManager;

	float m_FPS = 0;
	Vector2f m_Resolution;

	void HandleInput();
	void Update();
	void Draw();
};

