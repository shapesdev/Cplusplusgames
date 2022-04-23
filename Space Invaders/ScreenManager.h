#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include "GameScreen.h"
#include "ScreenManagerRemoteControl.h"
#include "SelectScreen.h"
#include "BitmapStore.h"

using namespace sf;
using namespace std;

class ScreenManager : public ScreenManagerRemoteControl
{
public:
	ScreenManager(Vector2i res);

	BitmapStore m_BS;

	void Update(float fps);
	void Draw(RenderWindow& window);
	void HandleInput(RenderWindow& window);

	void ScreenManagerRemoteControl::SwitchScreens(string screenToSwitchTo) {
		m_CurrentScreen = "" + screenToSwitchTo;
		m_Screens[m_CurrentScreen]->Initialize();
	}

	void ScreenManagerRemoteControl::LoadLevelInPlayMode(string screenToLoad) {
		SwitchScreens("Game");
	}

protected:
	string m_CurrentScreen = "Select";

private:
	map<string, unique_ptr<Screen>> m_Screens;
};

