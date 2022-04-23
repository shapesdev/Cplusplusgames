#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "InputHandler.h"
#include "UIPanel.h"
#include "ScreenManagerRemoteControl.h"

class InputHandler;

class Screen
{
public:
	virtual void Initialise();
	void virtual Update(float fps);
	void virtual Draw(RenderWindow& window);
	void HandleInput(RenderWindow& window);

	View m_View;

private:
	vector<shared_ptr<InputHandler>> m_InputHandlers;
	vector<unique_ptr<UIPanel>> m_Panels;

protected:
	void AddPanel(unique_ptr<UIPanel> p, ScreenManagerRemoteControl* smrc, shared_ptr<InputHandler> ih);
};

