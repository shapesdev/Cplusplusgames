#pragma once
#include "InputHandler.h"

class GameScreen;

class GameInputHandler : public InputHandler
{
public:
	void Initialise();
	void HandleGamepad() override;
	void HandleKeyPressed(Event& event, RenderWindow& window) override;
	void HandleKeyReleased(Event& event, RenderWindow& window) override;
};

