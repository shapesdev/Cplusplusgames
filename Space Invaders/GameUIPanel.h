#pragma once
#include "UIPanel.h"

class GameUIPanel : public UIPanel
{
public:
	GameUIPanel(Vector2i res);
	void Draw(RenderWindow& window) override;
};

