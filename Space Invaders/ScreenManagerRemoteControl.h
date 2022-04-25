#pragma once
#include <string>
#include <vector>
#include "GameObject.h"
#include "GameObjectSharer.h"

using namespace std;

class ScreenManagerRemoteControl
{
public:
	virtual void SwitchScreens(string screenToSwitchTo) = 0;
	virtual void LoadLevelInPlayMode(string screenToLoad) = 0;
	virtual vector<GameObject>& GetGameObjects() = 0;
	virtual GameObjectSharer& ShareGameObjectSharer() = 0;
};

