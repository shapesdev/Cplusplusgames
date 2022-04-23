#pragma once
#include "UIPanel.h"

class GameOverUIPanel : public UIPanel
{
public:
	GameOverUIPanel(Vector2i res);
	void virtual Draw(RenderWindow& window);

private:
	void InitialiseButtons();
};

