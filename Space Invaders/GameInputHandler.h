#pragma once
#include "InputHandler.h"
#include "PlayerUpdateComponent.h"
#include "TransformComponent.h"

class GameScreen;

class GameInputHandler : public InputHandler
{
public:
	void Initialise();
	void HandleGamepad() override;
	void HandleKeyPressed(Event& event, RenderWindow& window) override;
	void HandleKeyReleased(Event& event, RenderWindow& window) override;

private:
	shared_ptr<PlayerUpdateComponent> m_PUC;
	shared_ptr<TransformComponent> m_PTC;

	bool m_ButtonPressed = false;
};

