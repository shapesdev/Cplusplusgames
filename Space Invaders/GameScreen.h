#pragma once
#include "Screen.h"
#include "GameInputHandler.h"
#include "GameOverInputHandler.h"

class GameScreen : public Screen
{
public:
	static bool m_GameOver;

	GameScreen(ScreenManagerRemoteControl* smrc, Vector2i res);
	void Initialise() override;
	void virtual Update(float fps);
	void virtual Draw(RenderWindow& window);

private:
	ScreenManagerRemoteControl* m_ScreenManagerRemoteControl;
	shared_ptr<GameInputHandler> m_GIH;

	Texture m_BackgroundTexture;
	Sprite m_BackgroundSprite;
};

