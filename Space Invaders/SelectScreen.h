#pragma once
#include "Screen.h"

class SelectScreen : public Screen
{
public:
	SelectScreen(ScreenManagerRemoteControl* smrc, Vector2i res);
	void virtual Draw(RenderWindow& window);

private:
	ScreenManagerRemoteControl* m_ScreenManagerRemoteControl;
	Texture m_BackgroundTexture;
	Sprite m_BackgroundSprite;
};

