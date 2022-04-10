#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class HUD
{
public:
	HUD();
	Text GetMessage();
	Text GetLevel();
	Text GetTime();

	void SetLevel(String text);
	void SetTime(String text);

private:
	Font m_Font;
	Text m_StartText;
	Text m_TimeText;
	Text m_LevelText;
};

