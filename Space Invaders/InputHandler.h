#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Button.h"
#include "Screen.h"
#include "ScreenManagerRemoteControl.h"

using namespace sf;
using namespace std;

class Screen;

class InputHandler
{
public:
	void InitialiseInputHandler(ScreenManagerRemoteControl* sw,
		vector<shared_ptr<Button>>, View* pointerToUIView, Screen* parentScreen);
	void HandleInput(RenderWindow& window, Event& event);

	virtual void HandleGamepad();
	virtual void HandleKeyPressed(Event& event, RenderWindow& window);
	virtual void HandleKeyReleased(Event& event, RenderWindow& window);
	virtual void HandleLeftClick(string& buttonInterectedWith, RenderWindow& window);

	View* GetPointerToUIView();
	ScreenManagerRemoteControl* GetPointerToScreenManagerRemoteControl();
	Screen* GetParentScreen();

private:
	Screen* m_ParentScreen;
	vector<shared_ptr<Button>> m_Buttons;
	View* m_PointerToUIPanelView;
	ScreenManagerRemoteControl* m_ScreenManagerRemoteControl;
};

