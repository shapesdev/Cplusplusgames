#pragma once
#include "UIPanel.h"

class SelectUIPanel : public UIPanel
{
public:
	SelectUIPanel(Vector2i res);
	void virtual Draw(RenderWindow& window);

private:
	void InitialiseButtons();
};

