#pragma once
#include <string>
#include <vector>

using namespace std;

class ScreenManagerRemoteControl
{
public:
	virtual void SwitchScreens(string screenToSwitchTo) = 0;
	virtual void LoadLevelInPlayMode(string screenToLoad) = 0;
};

