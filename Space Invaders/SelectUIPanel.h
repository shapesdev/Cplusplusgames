#pragma once
#include "UIPanel.h"

class SelectUIPanel : UIPanel
{
public:
	SelectUIPanel(Vector2i res);
	void virtual Draw(RenderWindow& window);

private:
	void InitialiseButtons();
};

