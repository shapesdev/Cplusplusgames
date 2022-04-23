#pragma once
#include "InputHandler.h"

class SelectInputHandler : public InputHandler
{
public:
	void HandleKeyPressed(Event& event, RenderWindow& window) override;
	void HandleLeftClick(std::string& buttonInteractedWith, RenderWindow& window) override;
};

